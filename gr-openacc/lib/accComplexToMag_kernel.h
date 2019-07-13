#ifndef INCLUDED_OPENACC_ACCCOMPLEXTOMAG_KERNEL_H
#define INCLUDED_OPENACC_ACCCOMPLEXTOMAG_KERNEL_H

#include "acc_helper.h"

void accComplexToMag_init(acc_device_t deviceType, int devId);

void accComplexToMag_kernel(int noutput_items, const FComplex *in, float *out);

#endif
