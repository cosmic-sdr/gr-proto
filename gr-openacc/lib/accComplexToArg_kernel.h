#ifndef INCLUDED_OPENACC_ACCCOMPLEXTOARG_KERNEL_H
#define INCLUDED_OPENACC_ACCCOMPLEXTOARG_KERNEL_H

#include "acc_helper.h"
    
void accComplexToArg_init (acc_device_t deviceType, int devId, int threadID);

void accComplexToArg_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer, size_t out_device_buffer_size, d_void **out_device_buffer, int threadID);

void accComplexToArg_deviceData_free(d_void *in_device_buffer, d_void *out_device_buffer, int threadID);

void accComplexToArg_map(int noutput_items, const FComplex *in, d_void *in_device_buffer, float *out, d_void *out_device_buffer, int threadID);

void accComplexToArg_unmap(const FComplex *in, float *out, int threadID);

void accComplexToArg_kernel(int noutput_items, const FComplex *in, float *out, int threadID);

#endif
