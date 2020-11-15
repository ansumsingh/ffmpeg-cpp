#!/bin/bash
BUILD_EXAMPLES_FLAG=false
mkdir build

if [ "$1" == "--build-examples" ]; then $BUILD_EXAMPLES_FLAG=true
fi

echo BUILD_EXAMPLES_FLAG="${BUILD_EXAMPLES_FLAG}"

cmake -s . -B build -DBUILD_EXAMPLES=%BUILD_EXAMPLES_FLAG% -DCMAKE_TOOLCHAIN_FILE=${PWD}/dependencies/vcpkg/scripts/buildsystems/vcpkg.cmake 

cmake --build build

./build/test/Debug/ffmpegcpp-tests