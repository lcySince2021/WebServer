# !/bin/bash
set -xe
path=$(pwd)
echo $path
export LD_LIBRARY_PATH=$path/thirdparty/libhv/lib/:$LD_LIBRARY_PATH
./server
