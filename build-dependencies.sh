#!/bin/bash
set -ex

pushd dependencies/vcpkg

if [ ! -a vcpkg ]
then 
    ./bootstrap-vcpkg.sh
fi

./vcpkg update

./vcpkg integrate install

./vcpkg install ffmpeg catch2

popd