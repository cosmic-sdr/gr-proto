#ifndef INCLUDED_CLENABLED_CLMAGPHASETOCOMPLEX_KERNEL_H
#define INCLUDED_CLENABLED_CLMAGPHASETOCOMPLEX_KERNEL_H

#include "acc_helper.h"

void clMagPhaseToComplex_init(acc_device_t deviceType, int devSelector, int devId);

void clMagPhaseToComplex_kernel(int noutput_items, const float *a, const float *b, FComplex *c);

#endif
