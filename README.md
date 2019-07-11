**Step 0 -- Dependencies**

For Centos 7:
```
sudo yum install cmake boost cppunit python-mako clang swig numpy python-cheetah cppunit fftw fftw-devel qwt qwt-dvel pyqt4 doxygen zeromq scipy python-sphinx thrift uhd uhd-devel SDL libusb gsl gsl-devel wxPython zeromq3-devel python-txzmq SDL-devel pyusb
```

For Ubuntu 16.04:

```
sudo apt install libuhd-dev libuhd003.010.003 uhd-host locate  git swig cmake doxygen build-essential libboost-all-dev libtool libusb-1.0-0 libusb-1.0-0-dev libudev-dev libncurses5-dev libfftw3-bin libfftw3-dev libfftw3-doc libcppunit-1.14-0 libcppunit-dev libcppunit-doc ncurses-bin cpufrequtils python-numpy python-numpy-doc python-numpy-dbg python-scipy python-docutils qt4-bin-dbg qt4-default qt4-doc libqt4-dev libqt4-dev-bin python-qt4 python-qt4-dbg python-qt4-dev python-qt4-doc python-qt4-doc libqwt6abi1 libfftw3-bin libfftw3-dev libfftw3-doc ncurses-bin libncurses5 libncurses5-dev libncurses5-dbg libfontconfig1-dev libxrender-dev libpulse-dev swig g++ automake autoconf libtool python-dev libfftw3-dev libcppunit-dev libboost-all-dev libusb-dev libusb-1.0-0-dev fort77 libsdl1.2-dev python-wxgtk3.0 git libqt4-dev python-numpy ccache python-opengl libgsl-dev python-cheetah python-mako python-lxml doxygen qt4-default qt4-dev-tools libusb-1.0-0-dev libqwtplot3d-qt5-dev pyqt4-dev-tools python-qwt5-qt4 cmake git wget libxi-dev gtk2-engines-pixbuf r-base-dev python-tk liborc-0.4-0 liborc-0.4-dev libasound2-dev python-gtk2 libzmq3-dev libzmq5 python-requests python-sphinx libcomedi-dev python-zmq libqwt-dev libqwt6abi1 python-six libgps-dev libgps23 gpsd gpsd-clients python-gps python-setuptools
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
**Step 4 -- gr-cosmic**
```
cd $PROJECT_DIR/gr-cosmic
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local ..
make -j 8 install
```

**Step 5 -- PoCL, clFFT and gr-clenabled**
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

# Build & (local) Install gr-openacc

cd $PROJECT_DIR/gr-openacc
mkdir build
cd build
# TR_MODE = 0 for OpenACC
# TR_MODE = 1 for OpenMP3
# TR_MODE = 2 for OpenMP4
# TR_MODE = 3 for MCL 
//On Oswald1
cmake3 -DTR_MODE=0 -DCUDA_ROOT=/usr/local/cuda -DOpenCL_INCLUDE_DIR=/usr/local/cuda/targets/x86_64-linux/include/CL -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local -DGnuradio_DIR=$PROJECT_DIR/gnuradio-3.7.13.4/cmake/Modules -Wno-dev ..
//On Xavier2
cmake -DTR_MODE=0 -DCUDA_ROOT=/usr/local/cuda -DOpenCL_INCLUDE_DIR=/usr/local/include -DOpenCL_LIBRARY=/usr/lib/aarch64-linux-gnu/libOpenCL.so -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local -DGnuradio_DIR=$PROJECT_DIR/gnuradio-3.7.13.4/cmake/Modules -Wno-dev .. 
////////////////////////////////////////////////
//To generate OpenMP3 code, use the following.//
////////////////////////////////////////////////
//On Oswald1
cmake -DTR_MODE=1 -DCUDA_ROOT=/usr/local/cuda -DOpenCL_INCLUDE_DIR=/usr/local/cuda/targets/x86_64-linux/include/CL -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local -DGnuradio_DIR=$PROJECT_DIR/gnuradio-3.7.13.4/cmake/Modules -Wno-dev ..
//On Xavier2
cmake -DTR_MODE=1 -DCUDA_ROOT=/usr/local/cuda -DOpenCL_INCLUDE_DIR=/usr/local/include -DOpenCL_LIBRARY=/usr/lib/aarch64-linux-gnu/libOpenCL.so -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local -DGnuradio_DIR=$PROJECT_DIR/gnuradio-3.7.13.4/cmake/Modules -Wno-dev .. 

make -j install


# Run GR-Companion
gnuradio-companion
```
