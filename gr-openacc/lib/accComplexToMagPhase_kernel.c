#include "accComplexToMagPhase_kernel.h"

#include "math.h"
#ifdef USE_FAST_ATAN2
#include "fast_atan2f.c"
#endif

void accComplexToMagPhase_init(acc_device_t deviceType, int devId, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3
    acc_init(deviceType);
#endif
}

void accComplexToMagPhase_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer, size_t out_device_buffer_size, d_void **out_device_buffer1, d_void **out_device_buffer2, int threadID) {
	HI_set_context();
	*in_device_buffer = (d_void *)acc_malloc(in_device_buffer_size);
	*out_device_buffer1 = (d_void *)acc_malloc(out_device_buffer_size);
	*out_device_buffer2 = (d_void *)acc_malloc(out_device_buffer_size);
}

void accComplexToMagPhase_deviceData_free(d_void *in_device_buffer, d_void *out_device_buffer1, d_void *out_device_buffer2, int threadID) {
	acc_free(in_device_buffer);
	acc_free(out_device_buffer1);
	acc_free(out_device_buffer2);
}

void accComplexToMagPhase_map(int noutput_items, const FComplex *in, d_void *in_device_buffer, float *out1, d_void *out_device_buffer1, float *out2, d_void *out_device_buffer2, int threadID) {
	HI_set_context();
	acc_map_data((h_void *)in, in_device_buffer, noutput_items*sizeof(const FComplex));
	acc_map_data((h_void *)out1, out_device_buffer1, noutput_items*sizeof(float));
	acc_map_data((h_void *)out2, out_device_buffer2, noutput_items*sizeof(float));
}

void accComplexToMagPhase_unmap(const FComplex *in, float *out1, float *out2, int threadID) {
	acc_unmap_data((h_void *)in);
	acc_unmap_data((h_void *)out1);
	acc_unmap_data((h_void *)out2);
}

void accComplexToMagPhase_kernel(int noutput_items, const FComplex *in, float *out0, float *out1, int threadID) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	if( acc_is_present((h_void *)in, noutput_items*sizeof(const FComplex)) ) {
		acc_update_device((h_void *)in, noutput_items*sizeof(const FComplex));
	}

	#pragma acc kernels loop gang worker pcopyin(in[0:noutput_items]) pcopyout(out0[0:noutput_items], out1[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
        float aval = in[i].imag;
        float bval = in[i].real;
		out0[i] = sqrt(aval*aval+bval*bval);
#ifdef USE_FAST_ATAN2
		out1[i] = fast_atan2f(aval,bval);
#else
		out1[i] = atan2(aval,bval);
#endif
	}   

	if( acc_is_present((h_void *)out0, noutput_items*sizeof(float)) ) {
		acc_update_self((h_void *)out0, noutput_items*sizeof(float));
	}
	if( acc_is_present((h_void *)out1, noutput_items*sizeof(float)) ) {
		acc_update_self((h_void *)out1, noutput_items*sizeof(float));
	}
}
