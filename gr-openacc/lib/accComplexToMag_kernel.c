#include "accComplexToMag_kernel.h"

#ifdef _OPENARC_
#include "math.h"
#endif

void accComplexToMag_init(acc_device_t deviceType, int devId, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3
    acc_init(deviceType);
#endif
}

void accComplexToMag_deviceData_alloc(int noutput_items, const FComplex *in, float *out, int threadID) {
	acc_create((h_void *)in, noutput_items*sizeof(const FComplex));
	acc_create((h_void *)out, noutput_items*sizeof(float));
}

void accComplexToMag_deviceData_free(int noutput_items, const FComplex *in, float *out, int threadID) {
	acc_delete((h_void *)in, noutput_items*sizeof(const FComplex));
	acc_delete((h_void *)out, noutput_items*sizeof(float));
}

void accComplexToMag_kernel(int noutput_items, const FComplex *in, float *out, int threadID) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	HI_set_context();
	acc_update_device((h_void *)in, noutput_items*sizeof(const FComplex));

	#pragma acc kernels loop gang worker present(in[0:noutput_items]) present(out[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
		float aval = in[i].imag;
		float bval = in[i].real;
		out[i] = sqrt(aval*aval+bval*bval);
	}   

	acc_update_self((h_void *)out, noutput_items*sizeof(float));

}

