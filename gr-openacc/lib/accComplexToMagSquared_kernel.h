#ifndef INCLUDED_OPENACC_ACCCOMPLEXTOMAGSQUARED_KERNEL_H
#define INCLUDED_OPENACC_ACCCOMPLEXTOMAGSQUARED_KERNEL_H

#include "acc_helper.h"

void accComplexToMagSquared_init(acc_device_t deviceType, int devId, int threadID);

void accComplexToMagSquared_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer, size_t out_device_buffer_size, d_void **out_device_buffer, int threadID);

void accComplexToMagSquared_deviceData_free(d_void *in_device_buffer, d_void *out_device_buffer, int threadID);

void accComplexToMagSquared_map(int noutput_items, const FComplex *in, d_void *in_device_buffer, float *out, d_void *out_device_buffer, int threadID);

void accComplexToMagSquared_unmap(const FComplex *in, float *out, int threadID);

void accComplexToMagSquared_kernel(int noutput_items, const FComplex *in, float *out, int threadID);

#endif
