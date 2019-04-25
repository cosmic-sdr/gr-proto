#ifndef INCLUDED_CLENABLED_CLLOG_KERNEL_H
#define INCLUDED_CLENABLED_CLLOG_KERNEL_H

#include "acc_helper.h"
#include <math.h>

void clLog_init (acc_device_t deviceType, int devSelector, int devId);

void clLog_kernel( int noutput_items, float n_val, float k_val, unsigned int localWGSize, const float * in1, float * out );

#endif
