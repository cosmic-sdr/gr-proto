#ifndef INCLUDED_CLENABLED_ACC_HELPER_H
#define INCLUDED_CLENABLED_ACC_HELPER_H

#include "openacc.h"

#define OCLTYPE_GPU 1
#define OCLTYPE_ACCELERATOR 2
#define OCLTYPE_CPU 3
#define OCLTYPE_ANY 4

#define OCLDEVICESELECTOR_FIRST 1
#define OCLDEVICESELECTOR_SPECIFIC 2

struct FComplexStruct {
    float real;
    float imag;
};

typedef struct FComplexStruct FComplex;

//void acc_initializer(acc_device_t deviceType, int devSelector, int devId);

#endif
