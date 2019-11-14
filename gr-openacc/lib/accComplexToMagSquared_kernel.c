#include "accComplexToMagSquared_kernel.h"

#ifdef _OPENARC_
#include "math.h"
#endif

void accComplexToMagSquared_init(acc_device_t deviceType, int devId, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3
    acc_init(deviceType);
#endif
}

void accComplexToMagSquared_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer, size_t out_device_buffer_size, d_void **out_device_buffer, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2
	HI_set_context();
#endif
	*in_device_buffer = (d_void *)acc_malloc(in_device_buffer_size);
	*out_device_buffer = (d_void *)acc_malloc(out_device_buffer_size);
}

void accComplexToMagSquared_deviceData_free(d_void *in_device_buffer, d_void *out_device_buffer, int threadID) {
	acc_free(in_device_buffer);
	acc_free(out_device_buffer);
}

void accComplexToMagSquared_map(int noutput_items, const FComplex *in, d_void *in_device_buffer, float *out, d_void *out_device_buffer, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2
	HI_set_context();
#endif
	acc_map_data((h_void *)in, in_device_buffer, noutput_items*sizeof(const FComplex));
	acc_map_data((h_void *)out, out_device_buffer, noutput_items*sizeof(float));
}

void accComplexToMagSquared_unmap(const FComplex *in, float *out, int threadID) {
	acc_unmap_data((h_void *)in);
	acc_unmap_data((h_void *)out);
}

void accComplexToMagSquared_kernel(int noutput_items, const FComplex *in, float *out, int threadID) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	if( acc_is_present((h_void *)in, noutput_items*sizeof(const FComplex)) ) {
		acc_update_device((h_void *)in, noutput_items*sizeof(const FComplex));
	}

	#pragma acc kernels loop gang worker pcopyin(in[0:noutput_items]) pcopyout(out[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
		float aval = in[i].imag;
		float bval = in[i].real;
		out[i] = aval*aval+bval*bval;
	}   

	if( acc_is_present((h_void *)out, noutput_items*sizeof(float)) ) {
		acc_update_self((h_void *)out, noutput_items*sizeof(float));
	}
}
