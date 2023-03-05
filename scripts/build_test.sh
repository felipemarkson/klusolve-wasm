source ./scripts/build.sh

current_path=`pwd`
lib_path=$current_path"/libklusolve"
export LD_LIBRARY_PATH=$lib_path/lib:$LD_LIBRARY_PATH

gcc -L$lib_path/lib -I$lib_path/include -lklusolve -Wall -o test_wasm/main test_wasm/main.c