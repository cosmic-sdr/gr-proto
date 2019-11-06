#ifndef INCLUDED_OPENACC_ACCCOMPLEXTOMAGPHASE_KERNEL_H
#define INCLUDED_OPENACC_ACCCOMPLEXTOMAGPHASE_KERNEL_H

#include "acc_helper.h"

void accComplexToMagPhase_init(acc_device_t deviceType, int devId, int threadID);

void accComplexToMagPhase_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer, size_t out_device_buffer_size, d_void **out_device_buffer1, d_void **out_device_buffer2, int threadID);

void accComplexToMagPhase_deviceData_free(d_void *in_device_buffer, d_void *out_device_buffer1, d_void **out_device_buffer2, int threadID);

void accComplexToMagPhase_map(int noutput_items, const FComplex *in, d_void *in_device_buffer, float *out1, d_void *out_device_buffer1, float *out2, d_void *out_device_buffer2, int threadID);

void accComplexToMagPhase_unmap(const FComplex *in, float *out1, float *out2, int threadID);

void accComplexToMagPhase_kernel(int noutput_items, const FComplex *in, float *out0, float *out1, int threadID);

#endif
