#!/bin/bash
DOCKER_IMAGE_TAG=ffmpeg-cpp-build-env
DEBUGGER_IMAGE_NAME=ffmpeg-cpp-debug
docker run -it --rm --name ${DEBUGGER_IMAGE_NAME}  -v "${PWD}":/workspace -w /workspace ${DOCKER_IMAGE_TAG}