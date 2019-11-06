#include "accComplexToArg_kernel.h"

#include "math.h"
#ifdef USE_FAST_ATAN2
#include "fast_atan2f.c"
#endif

void accComplexToArg_init(acc_device_t deviceType, int devId, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3
    acc_init(deviceType);
#endif
}

void accComplexToArg_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer, size_t out_device_buffer_size, d_void **out_device_buffer, int threadID) {
	HI_set_context();
	*in_device_buffer = (d_void *)acc_malloc(in_device_buffer_size);
	*out_device_buffer = (d_void *)acc_malloc(out_device_buffer_size);
}

void accComplexToArg_deviceData_free(d_void *in_device_buffer, d_void *out_device_buffer, int threadID) {
	acc_free(in_device_buffer);
	acc_free(out_device_buffer);
}

void accComplexToArg_map(int noutput_items, const FComplex *in, d_void *in_device_buffer, float *out, d_void *out_device_buffer, int threadID) {
	HI_set_context();
	acc_map_data((h_void *)in, in_device_buffer, noutput_items*sizeof(const FComplex));
	acc_map_data((h_void *)out, out_device_buffer, noutput_items*sizeof(float));
}

void accComplexToArg_unmap(const FComplex *in, float *out, int threadID) {
	acc_unmap_data((h_void *)in);
	acc_unmap_data((h_void *)out);
}

void accComplexToArg_kernel(int noutput_items, const FComplex *in, float *out, int threadID) {
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
#ifdef USE_FAST_ATAN2
		out[i] = fast_atan2f(in[i].imag,in[i].real);
#else
		out[i] = atan2(in[i].imag,in[i].real);
#endif
	}   

	if( acc_is_present((h_void *)out, noutput_items*sizeof(float)) ) {
		acc_update_self((h_void *)out, noutput_items*sizeof(float));
	}
}
