#!/bin/bash
set -ex

pushd dependencies/vcpkg

if [ ! -a vcpkg ]
then 
    ./bootstrap-vcpkg.sh
fi



./vcpkg install ffmpeg catch2 --triplet x64-linux

popd