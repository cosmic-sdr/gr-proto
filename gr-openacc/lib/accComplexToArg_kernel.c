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

void accComplexToArg_deviceData_alloc(int noutput_items, const FComplex *in, float *out, int threadID) {
	acc_create((h_void *)in, noutput_items*sizeof(const FComplex));
	acc_create((h_void *)out, noutput_items*sizeof(float));
}

void accComplexToArg_deviceData_free(int noutput_items, const FComplex *in, float *out, int threadID) {
	acc_delete((h_void *)in, noutput_items*sizeof(const FComplex));
	acc_delete((h_void *)out, noutput_items*sizeof(float));
}

void accComplexToArg_kernel(int noutput_items, const FComplex *in, float *out, int threadID) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	//HI_set_context();
	//acc_pcreate((h_void *)in, noutput_items*sizeof(const FComplex));
	//acc_pcreate((h_void *)out, noutput_items*sizeof(float));
	//acc_update_device((h_void *)in, noutput_items*sizeof(const FComplex));

	#pragma acc kernels loop gang worker copyin(in[0:noutput_items]) copyout(out[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
#ifdef USE_FAST_ATAN2
		out[i] = fast_atan2f(in[i].imag,in[i].real);
#else
		out[i] = atan2(in[i].imag,in[i].real);
#endif
	}   

	//acc_update_self((h_void *)out, noutput_items*sizeof(float));
}
