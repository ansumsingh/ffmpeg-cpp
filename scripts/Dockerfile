FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y g++ \
    curl \
    unzip \
    tar \
    git \
    yasm \
    make

RUN apt update && apt install -y tzdata cmake 
