#ifndef INCLUDED_OPENACC_ACCMAGPHASETOCOMPLEX_KERNEL_H
#define INCLUDED_OPENACC_ACCMAGPHASETOCOMPLEX_KERNEL_H

#include "acc_helper.h"

void accMagPhaseToComplex_init(acc_device_t deviceType, int devId, int threadID);

void accMagPhaseToComplex_kernel(int noutput_items, const float *a, const float *b, FComplex *c, int threadID);

#endif
