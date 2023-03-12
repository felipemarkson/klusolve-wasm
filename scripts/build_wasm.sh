rm -rf build
rm -rf Lib
rm -rf libklusolve_wasm
rm -r Test/KLD*

mkdir build
cd build
emcmake cmake   -DCMAKE_BUILD_TYPE=Release \
                -DCMAKE_INSTALL_PREFIX=../libklusolve_wasm \
                -DCMAKE_PROJECT_INCLUDE=wasm.cmake \
                ..
emmake make
emmake make install
cd ..