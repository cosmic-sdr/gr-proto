#ifndef INCLUDED_OPENACC_ACCCOMPLEXTOMAGSQUARED_KERNEL_H
#define INCLUDED_OPENACC_ACCCOMPLEXTOMAGSQUARED_KERNEL_H

#include "acc_helper.h"

void accComplexToMagSquared_init(acc_device_t deviceType, int devId, int threadID);

void accComplexToMagSquared_kernel(int noutput_items, const FComplex *in, float *out, int threadID);

#endif
