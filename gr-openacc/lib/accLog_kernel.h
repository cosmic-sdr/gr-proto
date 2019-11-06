#ifndef INCLUDED_OPENACC_ACCLOG_KERNEL_H
#define INCLUDED_OPENACC_ACCLOG_KERNEL_H

#include "acc_helper.h"
#include <math.h>

void accLog_init (acc_device_t deviceType, int devId, int threadID);

void accLog_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer, size_t out_device_buffer_size, d_void **out_device_buffer, int threadID);

void accLog_deviceData_free(d_void *in_device_buffer, d_void *out_device_buffer, int threadID);

void accLog_map(int noutput_items, const float *in, d_void *in_device_buffer, float *out, d_void *out_device_buffer, int threadID);

void accLog_unmap(const float *in, float *out, int threadID);

void accLog_kernel( int noutput_items, float n_val, float k_val, const float * in1, float * out , int threadID);

#endif
