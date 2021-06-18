#include <tdv/utils/recognizer_utils/RecognizerUtils.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>


namespace tdv
{
namespace utils
{
namespace recognizer_utils
{

void construct_fda_points(
	const tdv::data::Context& fitter,
	std::vector<cv::Point2f> &dst_points,
	int i_w, int i_h)
{
	std::vector<int> fda_mapping;
	std::vector<int> mouth_center;
	//                 {0,   1,    2,   3,   4,   5,   6,   7,   8,   9,  10,  11, 12,  13, 14,  15,  16, 17, 18,  19, 20};
	if (fitter["fitter_type"].get<std::string>() == "mesh") // mesh
	{
		fda_mapping =  {70, 105, 107, 336, 334, 300,  33, -1, 133, 362, -1, 263, 93, 218,  1, 294, 361, 78, -1, 308, 152};
		mouth_center = {13, 14};
	}

	for (auto &ind: fda_mapping)
	{
		if (ind != -1)
			dst_points.push_back(cv::Point2f(fitter["keypoints"][ind][0].get<double>() * i_w,
											fitter["keypoints"][ind][1].get<double>() * i_h));
		else
			dst_points.push_back(cv::Point2f(-1.f, -1.f));
	}
	dst_points[18] = cv::Point2f(fitter["mouth"][0].get<double>() * i_w, fitter["mouth"][1].get<double>() * i_h);
	dst_points[7] = cv::Point2f(fitter["left_eye"][0].get<double>() * i_w, fitter["left_eye"][1].get<double>() * i_h);
	dst_points[10] = cv::Point2f(fitter["right_eye"][0].get<double>() * i_w, fitter["right_eye"][1].get<double>() * i_h);
}

cv::Matx23f estimate_scaled_rigid_transform(
	const std::vector<cv::Point2f> &src,
	const std::vector<cv::Point2f> &dst,
	const int iterations_count=10)
{
	std::vector<float> weights(src.size(), 1.f);

	std::vector<float> temp(src.size());

	for(int iterations = 0; ; ++iterations)
	{
		// scaled rigid transform is just a matrix:
		//    a b c
		//   -b a d
		// with arbitrary a, b, c and d

		// here we will iteratively compute it, reweighting points pairs by they error from prev iteration

		float sa[4][4], sb[4], sr[4];

		std::memset(sa, 0, sizeof(sa));
		std::memset(sb, 0, sizeof(sb));
		std::memset(sr, 0, sizeof(sr));

		for(size_t i = 0; i < src.size(); ++i)
		{
			const cv::Point2f &a = src[i];
			const cv::Point2f &b = dst[i];
			const float w = weights[i];

			#if 0
			// naive and without weights
			sa[0][0] += a.x * a.x  +  a.y * a.y;
			sa[0][1] += a.x * a.y  +  a.y * (-a.x);  // = 0
			sa[0][2] += a.x * 1    +  a.y * 0;
			sa[0][3] += a.x * 0    +  a.y * 1;

			sa[1][0] += a.y * a.x  +  (-a.x) * a.y;
			sa[1][1] += a.y * a.y  +  (-a.x) * (-a.x);
			sa[1][2] += a.y * 1    +  (-a.x) * 0;
			sa[1][3] += a.y * 0    +  (-a.x) * 1;

			sa[2][0] += 1 * a.x    +  0 * a.y;
			sa[2][1] += 1 * a.y    +  0 * (-a.x);
			sa[2][2] += 1 * 1      +  0 * 0;
			sa[2][3] += 1 * 0      +  0 * 1;

			sa[3][0] += 0 * a.x    +  1 * a.y;
			sa[3][1] += 0 * a.y    +  1 * (-a.x);
			sa[3][2] += 0 * 1      +  1 * 0;
			sa[3][3] += 0 * 0      +  1 * 1;

			sb[0] += a.x * b.x     + a.y * b.y;
			sb[1] += a.y * b.x     + (-a.x) * b.y;
			sb[2] += 1 * b.x       + 0 * b.y;
			sb[3] += 0 * b.x       + 1 * b.y;
			#else

			sa[0][0] += w * ( a.x * a.x  +  a.y * a.y );
			sa[0][2] += w * ( a.x );
			sa[0][3] += w * ( a.y );
			sa[1][0] += w * ( a.y * a.x  -  a.x * a.y );
			sa[2][2] += w * ( 1.f );

			sb[0] += w * ( a.x * b.x + a.y * b.y );
			sb[1] += w * ( a.y * b.x - a.x * b.y );
			sb[2] += w * ( b.x );
			sb[3] += w * ( b.y );
			#endif
		}

		sa[1][1] = sa[0][0];
		sa[1][2] = sa[0][3];
		sa[1][3] = - sa[0][2];

		sa[2][0] = sa[0][2];
		sa[2][1] = sa[0][3];

		sa[3][0] = sa[0][3];
		sa[3][1] = -sa[0][2];
		sa[3][3] = sa[2][2];


		float sw[4];
		for(int i = 0; i < 4; ++i)
			sw[i] = 1.f / sqrt( std::abs<float>(sa[i][i]) + 1e-6 );


		for(int i = 0; i < 4; ++i)
		{
			sb[i] *= sw[i];

			for(int j = 0; j < 4; ++j)
				sa[i][j] *= sw[i] * sw[j];
		}

		const bool solved = cv::solve(
			cv::Mat_<float>(4, 4, (float*) sa),
			cv::Mat_<float>(4, 1, (float*) sb),
			cv::Mat_<float>(4, 1, (float*) sr),
			cv::DECOMP_SVD);

		for(int i = 0; i < 4; ++i)
			sr[i] *= sw[i];

		if(iterations >= iterations_count)
		{
			cv::Matx23f result;
			result(0, 0) = sr[0];
			result(0, 1) = sr[1];
			result(0, 2) = sr[2];
			result(1, 0) = -sr[1];
			result(1, 1) = sr[0];
			result(1, 2) = sr[3];
			return result;
		}


		for(size_t i = 0; i < src.size(); ++i)
		{
			const cv::Point2f &a = src[i];
			const cv::Point2f &b = dst[i];

			cv::Point2f c;
			c.x =   a.x * sr[0] + a.y * sr[1] + sr[2];
			c.y = - a.x * sr[1] + a.y * sr[0] + sr[3];

			weights[i] = cv::norm(b-c);
		}

		temp = weights;

		std::nth_element(
			temp.data(),
			temp.data() + temp.size() / 2,
			temp.data() + temp.size());

		const float nw = temp[temp.size() / 2];

		for(size_t i = 0; i < src.size(); ++i)
			weights[i] = 1.f / (nw + weights[i] + 1e-6);
	}
}

cv::Matx23f makeCrop2ImageByPoints(const tdv::data::Context& fitter, cv::Mat& image, const int base_crop_size)
{
	std::vector<cv::Point2f> constructed_points;

	construct_fda_points(fitter, constructed_points, image.cols, image.rows);

	static const int target_points_count = 5;
	static const int crop_size_src = 112;
	cv::Point2f crop_points[target_points_count] = {
		cv::Point2f(38.30f, 51.70f),
		cv::Point2f(73.53f, 51.50f),
		cv::Point2f(56.00f, 71.70f),
		cv::Point2f(41.55f, 92.37f),
		cv::Point2f(70.73f, 92.20f),
	};

	float scale_factor = base_crop_size * (1.0 / crop_size_src);

	for (int i = 0; i < target_points_count; i++)
	{
		crop_points[i].x *= scale_factor;
		crop_points[i].y *= scale_factor;
	}

	const cv::Point2f image_points[target_points_count] = {
		constructed_points[ 7],
		constructed_points[10],
		constructed_points[14],
		constructed_points[17],
		constructed_points[19],
	};

	const cv::Matx23f crop2image =
		estimate_scaled_rigid_transform(
			std::vector<cv::Point2f> (crop_points,  crop_points  + target_points_count ),
			std::vector<cv::Point2f> (image_points, image_points + target_points_count ),
			10  // = iterations_count
		);

	return crop2image;

}

void warpAffine(
	cv::Mat &src,
	cv::Mat &dst,
	const cv::Matx23f &transform_m_input_,
	const cv::Size &dsize)
{
	cv::Matx23f transform_m = transform_m_input_;
	int flags = cv::WARP_INVERSE_MAP | cv::INTER_LINEAR;
	const int borderMode = cv::BORDER_CONSTANT;
	const cv::Scalar borderValue = cv::Scalar();

	const float t_a = transform_m(0, 0);
	const float t_b = transform_m(0, 1);
	const float t_c = transform_m(0, 2);
	const float t_d = transform_m(1, 0);
	const float t_e = transform_m(1, 1);
	const float t_f = transform_m(1, 2);

	// here we expect rigid transform with equal scale over x and y
	const float dst2src_scale = std::sqrt( (t_a * t_a + t_b * t_b + t_d * t_d + t_e * t_e) * 0.5f );

	int int_scale = 1;

	for(; ; ++int_scale)
	{
		if(dst2src_scale <= 2 * int_scale)
			break;
	}


	if(int_scale == 1)
	{
		cv::warpAffine(
			src,
			dst,
			transform_m,
			dsize,
			flags,
			borderMode,
			borderValue);

		return;
	}


	const float iis = 1.f / int_scale;

	transform_m(0, 0) = t_a * iis;
	transform_m(0, 1) = t_b * iis;
	transform_m(0, 2) = t_c - (t_a + t_b) * iis * (int_scale - 1) * 0.5f;
	transform_m(1, 0) = t_d * iis;
	transform_m(1, 1) = t_e * iis;
	transform_m(1, 2) = t_f - (t_d + t_e) * iis * (int_scale - 1) * 0.5f;


	cv::Mat tmp;
	cv::warpAffine(
		src,
		tmp,
		transform_m,
		cv::Size(dsize.width * int_scale, dsize.height * int_scale),
		flags,
		borderMode,
		borderValue);

	cv::resize(
		tmp,
		dst,
		dsize,
		0,
		0,
		cv::INTER_AREA);
}

} // recognizer_utils
} // namespace utils
} // namespace tdv