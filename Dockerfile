FROM ubuntu:20.04

RUN apt-get update && \
  apt-get -y --no-install-recommends install build-essential mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev \
  apt-get clean