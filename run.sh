# !/bin/bash
path=$(pwd)
echo $path
export LD_LIBRAR_PATH={$path}/thirdparty/libhv/lib/:$LD_LIBRARY_PATH
./server