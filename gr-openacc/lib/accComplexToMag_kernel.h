#ifndef INCLUDED_OPENACC_ACCCOMPLEXTOMAG_KERNEL_H
#define INCLUDED_OPENACC_ACCCOMPLEXTOMAG_KERNEL_H

#include "acc_helper.h"

void accComplexToMag_init(acc_device_t deviceType, int devId, int threadID);

void accComplexToMag_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer, size_t out_device_buffer_size, d_void **out_device_buffer, int threadID);

void accComplexToMag_deviceData_free(d_void *in_device_buffer, d_void *out_device_buffer, int threadID);

void accComplexToMag_deviceData_map(int noutput_items, const FComplex *in, d_void *in_device_buffer, float *out, d_void *out_device_buffer, int threadID);

void accComplexToMag_deviceData_unmap(const FComplex *in, float *out, int threadID);

void accComplexToMag_kernel(int noutput_items, const FComplex *in, float *out, int threadID);

#endif
