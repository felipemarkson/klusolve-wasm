rm -rf build
rm -rf Lib
rm -rf libklusolve
rm -r Test/KLD*

mkdir build
cd build
cmake   -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=../libklusolve \
        ..
make
make install
cd ..