from setuptools import setup, find_packages

__version__ = "1.0.0"

if __name__ == "__main__":
    setup(
        name="face_sdk",
        version=__version__,
        author = "Papil 11",
        author_email = "info@papil11.com",
        description="Package allows you to use Papil11 Face SDK in python language",
        url = "https://github.com/Papil11Development/sdk",
        packages=find_packages(),
        license=('AGPL-3.0'),
        python_requires=">=3.6",
        install_requires=["numpy>=1.16.2,<1.25", "opencv-python<=4.6.0.66,>4", "multipledispatch", "onnxruntime", "requests", "tqdm"],
        package_data={
            "face_sdk": [
                "for_linux/open_source_sdk/*",
                "for_linux/onnxruntime-linux-x86-64-shared-install-dir/*",
                "for_windows/open_source_sdk/*",
                "for_windows/onnxruntime-windows-x86-64-shared-install-dir/*",
                ]
            }
    )
