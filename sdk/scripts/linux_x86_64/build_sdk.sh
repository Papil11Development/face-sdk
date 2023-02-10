#!/bin/bash
set -e

echo "Download ONNX"

JAVA_HOME=${1:-""}
export PROJ_PATH=`pwd`
export CURRENT_ARCH=`uname -m`

if [[ -z ${JAVA_HOME} ]];
then
    WITH_JAVA="OFF"
else
    WITH_JAVA="ON"
fi
rm -rf 3rdparty/build && mkdir -p 3rdparty/build && cd 3rdparty/build
wget https://github.com/microsoft/onnxruntime/releases/download/v1.4.0/onnxruntime-linux-x64-1.4.0.tgz
tar -xvf onnxruntime-linux-x64-1.4.0.tgz && mv onnxruntime-linux-x64-1.4.0 onnxruntime

rm onnxruntime-linux-x64-1.4.0.tgz

# download opencv artifact

gdown https://drive.google.com/file/d/1mzowEQMFJbVdUdMfgz9ptxlQKhwKLLgj/view?usp=sharing -O opencv.zip 
unzip -o -d opencv opencv.zip

rm opencv.zip

cd ${PROJ_PATH}

gdown https://drive.google.com/u/0/uc?id=162OXlEh_18TLI0denqNysnBAGE3l8F-N -O models.zip 

rm -rf data/models/* && unzip models.zip -d data/models

rm models.zip

rm -rf build && mkdir build && cd build

export BUILD_DIR=`pwd`

export CMAKE_INSTALL_PREFIX="$(pwd)/make-install"

cmake \
    -DBUILD_SHARED=ON \
    -DWITH_SSE=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DWITH_SAMPLES=ON \
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} \
    -DTDV_OPENCV_DIR=${PROJ_PATH}/3rdparty/build/opencv \
    -DTDV_ONNXRUNTIME_DIR=${PROJ_PATH}/3rdparty/build/onnxruntime/ \
    -DWITH_JAVA=${WITH_JAVA} \
    -DJAVA_HOME=${JAVA_HOME} \
    ..

make install

cd make-install

export LIB_PATH="$(pwd)/lib"

cd python_api/face_sdk

mkdir for_linux
cd for_linux

mkdir open_source_sdk
cp ${LIB_PATH}/libopen_source_sdk.so $(pwd)/open_source_sdk

mkdir onnxruntime-linux-x86-64-shared-install-dir
cp ${LIB_PATH}/libonnxruntime.so $(pwd)/onnxruntime-linux-x86-64-shared-install-dir

cd ${BUILD_DIR}
