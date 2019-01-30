#ifndef INCLUDED_CLENABLED_CLCOMPLEXTOMAGPHASE_KERNEL_H
#define INCLUDED_CLENABLED_CLCOMPLEXTOMAGPHASE_KERNEL_H

#include "acc_helper.h"

void clComplexToMagPhase_init(acc_device_t deviceType, int devSelector, int devId);

void clComplexToMagPhase_kernel(int noutput_items, const FComplex *in, float *out0, float *out1);

#endif
