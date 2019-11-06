#ifndef INCLUDED_OPENACC_ACCMAGPHASETOCOMPLEX_KERNEL_H
#define INCLUDED_OPENACC_ACCMAGPHASETOCOMPLEX_KERNEL_H

#include "acc_helper.h"

void accMagPhaseToComplex_init(acc_device_t deviceType, int devId, int threadID);

void accMagPhaseToComplex_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer1, d_void **in_device_buffer2, size_t out_device_buffer_size, d_void **out_device_buffer, int threadID);

void accMagPhaseToComplex_deviceData_free(d_void *in_device_buffer1, d_void *in_device_buffer2, d_void *out_device_buffer, int threadID);

void accMagPhaseToComplex_map(int noutput_items, const float *in1, d_void *in_device_buffer1, const float *in2, d_void *in_device_buffer2, FComplex *out, d_void *out_device_buffer, int threadID);

void accMagPhaseToComplex_unmap(const float *in1, const float *in2, FComplex *out, int threadID);

void accMagPhaseToComplex_kernel(int noutput_items, const float *a, const float *b, FComplex *c, int threadID);

#endif
