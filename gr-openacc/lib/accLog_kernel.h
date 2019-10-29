#ifndef INCLUDED_OPENACC_ACCLOG_KERNEL_H
#define INCLUDED_OPENACC_ACCLOG_KERNEL_H

#include "acc_helper.h"
#include <math.h>

void accLog_init (acc_device_t deviceType, int devId, int threadID);

void accLog_kernel( int noutput_items, float n_val, float k_val, const float * in1, float * out , int threadID);

#endif
