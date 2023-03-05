rm -rf build
rm -rf Lib
rm -rf libklusolve
rm -r Test/KLD*

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../libklusolve -DCMAKE_PROJECT_INCLUDE=wasm.cmake ..
make
make install