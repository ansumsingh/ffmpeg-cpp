#!/bin/bash

set -ex

script=$1
DOCKER_IMAGE_TAG=ffmpeg-cpp-build-env

pushd scripts
ls

docker build -t ${DOCKER_IMAGE_TAG} .

popd

if [ "${script}" != "" ]
then
    echo "executing ${script}"
    docker run --rm -u $(id -u):$(id -g) -v "${PWD}":/workspace -w /workspace ${DOCKER_IMAGE_TAG} /workspace/${script} $2
fi
