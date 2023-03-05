source ./scripts/build_wasm.sh

current_path=`pwd`
klu_path=$current_path"/libklusolve"
lib_path=$klu_path"/lib"
header_path=$klu_path"/include"

emcc -I$header_path -sMAIN_MODULE test_wasm/main.c $lib_path/libklusolve.so -Wall -Oz -o test_wasm/main.js
cp $lib_path/libklusolve.so test_wasm/libklusolve.so

# echo "Output:"
# node Test_Felipe/main.js