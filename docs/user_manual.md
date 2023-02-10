Here are some useful information about SDK
# SDK
Face SDK can be successfully used in various domains and business cases, such as:
* face biometrics (access control systems, remote identification, user authorization by face); 
* intelligent video analytics (safe city, industrial safety, analyzing customer activity in stores or generic human analysis).

## Available Models
||||  
|--|--|--|  
|Face Detector :heavy_check_mark: |Face Mesh :heavy_check_mark: | Face Recognizer :heavy_check_mark:| 
|Gender Estimator :heavy_check_mark:| Age Estimator :heavy_check_mark:| Emotions Estimator :heavy_check_mark:| 
|Liveness Detector :heavy_check_mark:| Glass and Mask Detectors :heavy_check_mark:|Eyes Openness Estimator :heavy_check_mark:|
| Body Detector :heavy_check_mark:| Person Re-Identificator :heavy_check_mark:| Human Pose Estimator :heavy_check_mark:|

<details><summary>How can I use these awesome models?</summary>
<p>

* Face Detector - finds human faces on images to get crops for further processing.
* Face Mesh - finds face landmarks (keypoints). Theese points could be used to align face crop for further processing.
* Face Recognizer - this model extracts biometric templates from face crops. By comparing two patterns, you can determine whether they belong to the same person or two different people. So, using Face Recognizer you can solve vaious identification or verification tasks.
* Liveness Detector - checks if face crop, which you want to use to build biometric template belongs to real person. Thus, it helps you to understand that someone tries to fool your biometric system.
* Gender, Age and Emotions Estimators - estimates corresponding face attribute by face crop. Could be used to analyze humans. For example, if you own some shop, you can automaticly estimate your customers age and gender and use this information in your marketing.
* Glass and Mask Detectors - checks if person wears glasses or mask correspondingly. It's usefull to identify quarantine violators!
* Eyes Openness Estimator - checks if person's eyes are closed. Could be used to detect sleeping drivers or pilots.
* Body Detector - finds human bodies on images to get crops for further processing.
* Human Pose Estimator - estimates skeleton keypoints by body crops. For example, this model could help you to estimate how correctly a person performs physical exercises.
* Person Re-Identificator - like Face Recognizer, this model extracts templates but from body crops. Such templates are very useful when you solving human tracking task on video.




</p>
</details>

## APIs and Platforms support

|API Support|Linux x86-64| Windows| 
|--|--|--|
|C++            |:heavy_check_mark:|:heavy_check_mark:|
|Python         |:heavy_check_mark:|:heavy_check_mark:|
|C#             |:heavy_check_mark:|:heavy_check_mark:|
|Java           |:heavy_check_mark:|:heavy_check_mark:|
|JavaScript     |:heavy_check_mark:|:heavy_check_mark:|

## Run C++, Python and C# Demo Samples

There are 3 demo samles for C++, Python and C# API

### face_demo
Startup arguments:
* `--mode` - optional, operating mode, default value is "detection", see the list of available modes below
* `--input_image` - required, path to the input image file
* `--input_image2` - required for recognition mode, path to the second input image file
* `--sdk_path` - optional, the path to the installed SDK directory, default value is ".." to launch from the default location _build/make-install/bin_
* `--window` - optional, allows to disable displaying window with results (specify any value except of "yes"), default value is "yes"
* `--output` - optional, allows to disable printing results (points coordinates) in console (specify any value except of "yes"), default value is "yes"

Run the following commands from the _build/make-install/bin_ directory to execute the sample:

* С++ (Windows): 
```bash
.\face_demo.exe --sdk_path .. --mode detection --input_image ../../../test_images/face.jpg  
```
* С++ (Linux): 
```bash
LD_LIBRARY_PATH=../lib ./face_demo --sdk_path .. --mode landmarks --input_image ../../../test_images/landmarks.jpeg
```
* Python (Windows): 
```bash
python face_demo.py --sdk_path .. --mode recognition --input_image ../../../test_images/facerec_1.jpg --input_image2 ../../../test_images/facerec_2.jpeg
```

* Python (Linux): 
```bash
python3 face_demo.py --sdk_path .. --mode recognition --input_image ../../../test_images/facerec_1.jpg --input_image2 ../../../test_images/facerec_2.jpeg
```
* С# (Windows): 
```bash
.\csharp_face_demo.exe --sdk_path .. --input_image ../../../test_images/facerec_1.jpg --mode detection
```

* С# (Linux): 
```bash
./csharp_face_demo --sdk_path .. --input_image ../../../test_images/facerec_1.jpg --mode detection
```
#### Sample modes
* **detection** - Detects the face on the input image visualize bounding box. 
* **landmarks** - Estimates face keypoints and visualize them.
* **recognition** - Detects a face on each image, builds and compares face patterns. Prints matching result and the distance between templates. Draw the crops of detected faces.  
_**Note:** If there is more than one face detected on the image, sample will process the detection with greatest confidence._

### estimator_demo
Startup arguments:
* `--mode` - optional, operating mode, default value is "all", see the list of available modes below
* `--input_image` - required, path to the input image file
* `--sdk_path` - optional, the path to the installed SDK directory, default value is ".." to launch from the default location _build/make-install/bin_
* `--window` - optional, allows to disable displaying window with results (specify any value except of "yes"), default value is "yes"
* `--output` - optional, allows to disable printing results (points coordinates) in console (specify any value except of "yes"), default value is "yes"

Run the following commands from the _build/make-install/bin_ directory to execute the sample:

* С++ (Windows): 
```bash
./estimator_demo.exe --sdk_path .. --mode all --input_image ../../../test_images/face_attributes.jpg
```
* С++ (Linux): 
```bash
LD_LIBRARY_PATH=../lib ./estimator_demo --sdk_path .. --mode age --input_image ../../../test_images/age_gender.jpg
```
* Python (Windows): 
```bash
python estimator_demo.py --sdk_path .. --mode mask --input_image ../../../test_images/mask_glasses.jpeg
```
* Python (Linux): 
```bash
python3 estimator_demo.py --sdk_path .. --mode mask --input_image ../../../test_images/mask_glasses.jpeg
```
* C# (Windows):
```bash
.\csharp_estimator_demo.exe  --sdk_path .. --mode all --input_image ../../../test_images/face_attributes.jpg
```
* C# (Linux):
```bash
./csharp_estimator_demo  --sdk_path .. --mode all --input_image ../../../test_images/face_attributes.jpg
```
#### Sample modes
* **all** - Launch all modes.
* **age** - Estimates age. 
* **gender** - Estimates gender.
* **emotion** - Estimates emotions and provides confidence.  
* **liveness** - Estimates liveness also provides confidence and verdict.
* **mask** - Detects medical mask.
* **glasses** - Estimates glasses and provides confidence.
* **eye_openness** - Estimates eyes openness and provides confidence about each eye openness.

### body_demo
Startup arguments:
* `--mode` - optional, operating mode, default value is "detection", see the list of available modes below
* `--input_image` - required, path to the input image file
* `--sdk_path` - optional, the path to the installed SDK directory, default value is ".." to launch from the default location _build/make-install/bin_
* `--output` - optional, allows to disable printing results (points coordinates) in console (specify any value except of "yes"), default value is "yes"

Run the following commands from the _build/make-install/bin_ directory to execute the sample:

* С++ (Windows): 
```bash
./body_demo.exe --sdk_path .. --mode detection --input_image ../../../test_images/body.jpg
```
* С++ (Linux): 
```bash
LD_LIBRARY_PATH=../lib ./body_demo --sdk_path .. --mode detection --input_image ../../../test_images/body.jpg
```
* Python (Windows): 
```bash
python body_demo.py --sdk_path .. --mode detection --input_image ../../../test_images/body.jpg
```

* Python (Linux): 
```bash
python3 body_demo.py --sdk_path .. --mode detection --input_image ../../../test_images/body.jpg
```
* C# (Widows):
```bash
.\csharp_body_demo.exe --sdk_path .. --input_image ../../../test_images/body.jpg --mode detection
```

* C# (Linux):
```bash
./csharp_body_demo --sdk_path .. --input_image ../../../test_images/body.jpg --mode detection
```

#### Sample modes
* **detection** - Detects human body on the input image visualize bounding box. .
* **pose** - Estimates skeleton keypoints and visualize them. 
* **reidentification** - Computes template by body crop.

### Java Sample
Also there is minimal sample for Java with only face detector block.
#### Startup arguments:
* `--input_image` - required, path to the input image file
* `--sdk_path` - optional, the path to the installed SDK directory, default value is ".." to launch from the default location _build/make-install/bin_

 You can run it from _sdk/samples/java_ with command for Linux 
```bash
LD_LIBRARY_PATH=../../build/make-install/lib java -classpath ./bin com.face_detector_demo.face_detector_demo  ../../test_images/face.jpg ../../build/make-install
```
and from _sdk/build/make-install/bin_ for Windows 
```bash
java -classpath ./bin com.face_detector_demo.face_detector_demo  ../../test_images/face.jpg ../../build/make-install/
```

### JavaScript Sample
There JavaScript sample which shows how to use face detector in browser:

* Copy _data/models/face_detector_ folder to _src/javascript_api_ directory.
* Start any web-server in _src/javascript_api_. For example, run following command in folder.
    * Linux
      ```bash
      python3 -m http.server
      ```
    * Windows
      ```bash
      python -m http.server
      ```
* Go to localhost:8000 in your browser
* Click on face_detection.html
* On this html page you can open some local image from disk (from _sdk/test_images_ for example). There should be vizualised image with face bboxes. 
