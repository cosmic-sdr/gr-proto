*Step 0* -- Dependencies:

You need to have these packages on top of vanilla Centos 7 installation. They are already installed on Oswald01.
```
sudo yum install cmake boost cppunit python-mako clang swig numpy python-cheetah cppunit fftw fftw-devel qwt qwt-dvel pyqt4 doxygen zeromq scipy python-sphinx thrift uhd uhd-devel SDL libusb gsl gsl-devel wxPython zeromq3-devel python-txzmq SDL-devel pyusb
```

For Ubuntu, you need to have these packages installed:

```
sudo apt install cmake boost cppunit python-mako clang swig numpy python-cheetah fftw fftw-devel qwt qwt-dvel pyqt4 doxygen zeromq scipy python-sphinx thrift uhd uhd-devel SDL libusb gsl gsl-devel wxPython zeromq3-devel python-txzmq SDL-devel pyusb libcppunit-dev libboost-dev python-mako swig python-numpy python-cheetah fftw-dev python-qwt doxygen python-scipy sphinx-common thrift-compiler python-sdl2 libfftw3-dev python-lxml qt4-dev-tools libqwt-dev  python-qwt-qt5 libsdl-dev libzmq3-dev libcomedi-dev libgsl-dev
```
*Step 1* -- Source and Environment Variables:

Clone and prepare for local installation of clFFT, gnuradio and gr-cleanbled into ~/usr/local

```
# Clone this project and setup up project directory

git clone https://code.ornl.gov/cosmic-castle/gnuradio-custom.git
cd gnuradio-custom
export PROJECT_DIR=$PWD


# Setup environment variables (also add these to your ~/.bashrc)

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64 
export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/cuda/lib64
export PATH=$PATH:~/usr/local/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/usr/local/lib64
export PYTHONPATH=~/usr/local/lib64/python2.7/site-packages/
```

*Step 2* -- clFFT:

```
# Build & (local) Install clFFT

cd $PROJECT_DIR/clFFT
mkdir build
cd build

cmake3 -DOpenCL_INCLUDE_DIR=/usr/local/cuda-9.2/targets/x86_64-linux/include/CL/ -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DUSE_GPU=1 -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local -Wno-dev ../src/
make -j install
```

*Step 3* -- GNU Radio:

```
# Build & (local) Install gnuradio (latest stable release)

cd $PROJECT_DIR/gnuradio-3.7.13.4
mkdir build
cd build
cmake3 -DOpenCL_INCLUDE_DIR=/usr/local/cuda-9.2/targets/x86_64-linux/include/CL/ -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DUSE_GPU=1 -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local ..
make -j install
```
*Step 4* -- gr-clenabled:

```
# Build & (local) Install gr-clenabled

cd $PROJECT_DIR/gr-clenabled
mkdir build
cd build
cmake3 -DOpenCL_INCLUDE_DIR=/usr/local/cuda-9.2/targets/x86_64-linux/include/CL/ -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DUSE_GPU=1 -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local -DGnuradio_DIR=$PROJECT_DIR/gnuradio-3.7.13.4/cmake/Modules/ -Wno-dev ..
make -j install

# Run GR-Companion
gnuradio-companion
```
