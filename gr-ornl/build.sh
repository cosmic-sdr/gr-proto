rm -rf build
mkdir build
cd build
cmake -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/.local -DCMAKE_PREFIX_PATH=~/.local -DGnuradio_DIR=~/work/gnuradio-custom/gnuradio-3.7.13.4/cmake/Modules/ -Wno-dev ..
make -j install

