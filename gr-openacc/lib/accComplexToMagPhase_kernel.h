#ifndef INCLUDED_OPENACC_ACCCOMPLEXTOMAGPHASE_KERNEL_H
#define INCLUDED_OPENACC_ACCCOMPLEXTOMAGPHASE_KERNEL_H

#include "acc_helper.h"

void accComplexToMagPhase_init(acc_device_t deviceType, int devId);

void accComplexToMagPhase_kernel(int noutput_items, const FComplex *in, float *out0, float *out1);

#endif
