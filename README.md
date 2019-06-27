**Step 0 -- Dependencies**

For Centos 7:
```
sudo yum install cmake boost cppunit python-mako clang swig numpy python-cheetah cppunit fftw fftw-devel qwt qwt-dvel pyqt4 doxygen zeromq scipy python-sphinx thrift uhd uhd-devel SDL libusb gsl gsl-devel wxPython zeromq3-devel python-txzmq SDL-devel pyusb
```

For Ubuntu 16.04:

```
sudo apt install cmake boost cppunit python-mako clang swig numpy python-cheetah fftw fftw-devel qwt qwt-dvel pyqt4 doxygen zeromq scipy python-sphinx thrift uhd uhd-devel SDL libusb gsl gsl-devel wxPython zeromq3-devel python-txzmq SDL-devel pyusb libcppunit-dev libboost-dev python-mako swig python-numpy python-cheetah fftw-dev python-qwt doxygen python-scipy sphinx-common thrift-compiler python-sdl2 libfftw3-dev python-lxml qt4-dev-tools libqwt-dev  python-qwt-qt5 libsdl-dev libzmq3-dev libcomedi-dev libgsl-dev
```
**Step 1 -- Source and Environment Variables**

Clone and prepare for local installation of clFFT, gnuradio and gr-cleanbled into ~/usr/local

```
# Clone this project and setup up project directory

git clone https://code.ornl.gov/cosmic-castle/gnuradio-custom.git
cd gnuradio-custom
export PROJECT_DIR=$PWD


# Setup environment variables (also add these to your ~/.bashrc)

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(dirname $(locate libcuda.so | head -n 1)) 
export PATH=$PATH:~/usr/local/bin
export PYTHONPATH=$PYTHONPATH:~/usr/local/lib64/python2.7/site-packages/::~/usr/local/lib/python2.7/dist-packages/
export CUDA_HOME=/usr/local/cuda
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CUDA_HOME/lib64:~/usr/local/lib
```

**Step 2 -- GNU Radio**

```
# Build & (local) Install gnuradio (latest stable release)

cd $PROJECT_DIR/gnuradio-3.7.13.4
mkdir build
cd build
cmake -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local ..
make -j 8 install
```

**Step 3 -- USRP-antenna and IEEE-WIFI modules**
```
sudo cp -rf $PROJECT_DIR/simde/simde/ /usr/include/ 

cd $PROJECT_DIR/gr-ieee802-11
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local ..
make -j 8 install

cd $PROJECT_DIR/gr-foo
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local ..
make -j 8 install

sudo su
uhd_images_downloader # if the download doesn't proceed then make sure excl proxies are set properly in /root/.bashrc
cp /usr/lib/uhd/utils/uhd-usrp.rules /etc/udev/rules.d
udevadm control --reload-rules
udevadm trigger
exit


```




**Step 4 -- PoCL, clFFT and gr-clenabled**
```
# Build & (local) Install PoCL
```

```
# Build & (local) Install clFFT

cd $PROJECT_DIR/clFFT
mkdir build
cd build

cmake -DOpenCL_INCLUDE_DIR=/usr/local/cuda/targets/x86_64-linux/include/CL/ -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DUSE_GPU=1 -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local -Wno-dev ../src/
make -j install
```

```
# Build & (local) Install gr-clenabled

cd $PROJECT_DIR/gr-clenabled
mkdir build
cd build
cmake -DOpenCL_INCLUDE_DIR=/usr/local/cuda/targets/x86_64-linux/include/CL/ -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DUSE_GPU=1 -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local -DGnuradio_DIR=$PROJECT_DIR/gnuradio-3.7.13.4/cmake/Modules/ -Wno-dev ..
make -j install

# Run GR-Companion
gnuradio-companion
```
