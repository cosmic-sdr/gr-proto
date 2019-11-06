#include "accMagPhaseToComplex_kernel.h"

#include "math.h"

void accMagPhaseToComplex_init(acc_device_t deviceType, int devId, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3
    acc_init(deviceType);
#endif
}


void accMagPhaseToComplex_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer1, d_void **in_device_buffer2, size_t out_device_buffer_size, d_void **out_device_buffer, int threadID) {
	HI_set_context();
	*in_device_buffer1 = (d_void *)acc_malloc(in_device_buffer_size);
	*in_device_buffer2 = (d_void *)acc_malloc(in_device_buffer_size);
	*out_device_buffer = (d_void *)acc_malloc(out_device_buffer_size);
}

void accMagPhaseToComplex_deviceData_free(d_void *in_device_buffer1, d_void *in_device_buffer2, d_void *out_device_buffer, int threadID) {
	acc_free(in_device_buffer1);
	acc_free(in_device_buffer2);
	acc_free(out_device_buffer);
}

void accMagPhaseToComplex_map(int noutput_items, const float *in1, d_void *in_device_buffer1, const float *in2, d_void *in_device_buffer2, FComplex *out, d_void *out_device_buffer, int threadID) {
	HI_set_context();
	acc_map_data((h_void *)in1, in_device_buffer1, noutput_items*sizeof(const float));
	acc_map_data((h_void *)in2, in_device_buffer2, noutput_items*sizeof(const float));
	acc_map_data((h_void *)out, out_device_buffer, noutput_items*sizeof(FComplex));
}

void accMagPhaseToComplex_unmap(const float *in1, const float *in2, FComplex *out, int threadID) {
	acc_unmap_data((h_void *)in1);
	acc_unmap_data((h_void *)in2);
	acc_unmap_data((h_void *)out);
}

void accMagPhaseToComplex_kernel(int noutput_items, const float *a, const float *b, FComplex *c, int threadID) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	if( acc_is_present((h_void *)a, noutput_items*sizeof(const float)) ) {
		acc_update_device((h_void *)a, noutput_items*sizeof(const float));
	}
	if( acc_is_present((h_void *)b, noutput_items*sizeof(const float)) ) {
		acc_update_device((h_void *)b, noutput_items*sizeof(const float));
	}

	#pragma acc kernels loop gang worker pcopyin(a[0:noutput_items], b[0:noutput_items]) pcopyout(c[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
		float mag = a[i];
		float phase = b[i];
		float real = mag*cos(phase);
		float imag = mag*sin(phase);
		c[i].real = real;
		c[i].imag = imag;
	}   

	if( acc_is_present((h_void *)c, noutput_items*sizeof(FComplex)) ) {
		acc_update_self((h_void *)c, noutput_items*sizeof(FComplex));
	}
}
