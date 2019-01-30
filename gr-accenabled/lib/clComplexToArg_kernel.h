#ifndef INCLUDED_CLENABLED_CLCOMPLEXTOARG_KERNEL_H
#define INCLUDED_CLENABLED_CLCOMPLEXTOARG_KERNEL_H

#include "acc_helper.h"
    
void clComplexToArg_init (acc_device_t deviceType, int devSelector, int devId);

void clComplexToArg_kernel(int noutput_items, const FComplex *in, float *out);

#endif
