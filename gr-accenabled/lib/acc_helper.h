#ifndef INCLUDED_CLENABLED_ACC_HELPER_H
#define INCLUDED_CLENABLED_ACC_HELPER_H

#include "openacc.h"

#define OCLTYPE_DEFAULT (1 << 0)
#define OCLTYPE_CPU (1 << 1)
#define OCLTYPE_GPU (1 << 2)
#define OCLTYPE_ACCELERATOR (1 << 3)
#define OCLTYPE_CUSTOM (1 << 4)
#define OCLTYPE_ANY 0xFFFFFFFF

#define OCLDEVICESELECTOR_FIRST 1
#define OCLDEVICESELECTOR_SPECIFIC 2

struct FComplexStruct {
    float real;
    float imag;
};

typedef struct FComplexStruct FComplex;

//void acc_initializer(acc_device_t deviceType, int devSelector, int devId);

#endif
