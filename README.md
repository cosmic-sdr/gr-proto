
local installation
```
git clone https://code.ornl.gov/cosmic-castle/gnuradio-custom.git
cd gnuradio-custom

export PROJECT_DIR=$PWD
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64
export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/cuda/lib64
export PATH=$PATH:~/usr/local/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/usr/local/lib64
export PYTHONPATH=~/usr/local/lib64/python2.7/site-packages/

cd $PROJECT_DIR/gnuradio-3.7.13.4
mkdir build
cd build
cmake3 -DOpenCL_INCLUDE_DIR=/usr/local/cuda-9.2/targets/x86_64-linux/include/CL/ -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DUSE_GPU=1 -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local ..
make -j install

cd $PROJECT_DIR/gr-clenabled
mkdir build
cd build
cmake3 -DOpenCL_INCLUDE_DIR=/usr/local/cuda-9.2/targets/x86_64-linux/include/CL/ -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DUSE_GPU=1 -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DCMAKE_INSTALL_PREFIX=~/usr/local -DCMAKE_PREFIX_PATH=~/usr/local -DGnuradio_DIR=$PROJECT_DIR/gnuradio-3.7.13.4/cmake/Modules/ -Wno-dev ..
make -j install
```

root installation
```
mkdir /tmp/$USER
cd /tmp/$USER

git clone https://code.ornl.gov/cosmic-castle/gnuradio-custom.git
cd gnuradio-custom

sudo su
export PROJECT_DIR=$PWD
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64
export LIBRARY_PATH=$LIBRARY_PATH:/usr/local/cuda/lib64
export PATH=$PATH:/usr/local/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib64
export PYTHONPATH=/usr/local/lib64/python2.7/site-packages/


cd $PROJECT_DIR/gnuradio-3.7.13.4
mkdir build
cd build
cmake3 -DOpenCL_INCLUDE_DIR=/usr/local/cuda-9.2/targets/x86_64-linux/include/CL/ -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DUSE_GPU=1 -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON ..
make -j install

cd $PROJECT_DIR/gr-clenabled
mkdir build
cd build
cmake3 -DOpenCL_INCLUDE_DIR=/usr/local/cuda-9.2/targets/x86_64-linux/include/CL/ -DOpenCL_LIBRARY=/usr/local/cuda/lib64/libOpenCL.so -DUSE_GPU=1 -DBoost_USE_STATIC_LIBS=OFF -DBoost_USE_MULTITHREADED=ON  -DGnuradio_DIR=$PROJECT_DIR/gnuradio-3.7.13.4/cmake/Modules/ -Wno-dev ..
make -j install
```

