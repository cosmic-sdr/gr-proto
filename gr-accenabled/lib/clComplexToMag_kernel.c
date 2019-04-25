#include "clComplexToMag_kernel.h"

#ifdef _OPENARC_
#include "math.h"
#endif

void clComplexToMag_init(acc_device_t deviceType, int devSelector, int devId) {
#if !defined(TR_MODE) || TR_MODE == 0
    acc_init(deviceType);
    if( devSelector == OCLDEVICESELECTOR_SPECIFIC ) { 
        acc_set_device_num(devId, deviceType);
    }   
#endif
}

void clComplexToMag_kernel(int noutput_items, const FComplex *in, float *out) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	#pragma acc kernels loop gang worker copyin(in[0:noutput_items]) copyout(out[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
		float aval = in[i].imag;
		float bval = in[i].real;
		out[i] = sqrt(aval*aval+bval*bval);
	}   
}
