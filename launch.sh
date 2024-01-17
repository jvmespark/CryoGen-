#!/bin/bash -e
docker build -t doom-like -f Dockerfile .   # 1>&2
if [ ! -z $1 ]; then
  docker run -i --rm doom-like bash -c "cd /tmp/ && git clone -q https://github.com/$1/doom-like.git && cd doom-like && ./main.exe"
fi
