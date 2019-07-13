#ifndef INCLUDED_OPENACC_ACCCOMPLEXTOARG_KERNEL_H
#define INCLUDED_OPENACC_ACCCOMPLEXTOARG_KERNEL_H

#include "acc_helper.h"
    
void accComplexToArg_init (acc_device_t deviceType, int devId);

void accComplexToArg_kernel(int noutput_items, const FComplex *in, float *out);

#endif
