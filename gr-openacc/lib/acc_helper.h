#ifndef INCLUDED_OPENACC_ACC_HELPER_H
#define INCLUDED_OPENACC_ACC_HELPER_H

#include "openacc.h"

#define ACCTYPE_DEFAULT (1 << 0)
#define ACCTYPE_CPU (1 << 1)
#define ACCTYPE_GPU (1 << 2)
#define ACCTYPE_ACCELERATOR (1 << 3)
#define ACCTYPE_CUSTOM (1 << 4)
#define ACCTYPE_ANY 0xFFFFFFFF

#define ACCDEVICESELECTOR_FIRST 1
#define ACCDEVICESELECTOR_SPECIFIC 2

struct FComplexStruct {
    float real;
    float imag;
};

typedef struct FComplexStruct FComplex;

//void acc_initializer(acc_device_t deviceType, int devSelector, int devId);

#endif
