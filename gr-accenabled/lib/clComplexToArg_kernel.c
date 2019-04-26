#include "clComplexToArg_kernel.h"

#include "math.h"
#ifdef USE_FAST_ATAN2
#include "fast_atan2f.c"
#endif

void clComplexToArg_init(acc_device_t deviceType, int devSelector, int devId) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3
    acc_init(deviceType);
#if !defined(TR_MODE) || TR_MODE == 0
    if( devSelector == OCLDEVICESELECTOR_SPECIFIC ) { 
        acc_set_device_num(devId, deviceType);
    }   
#endif
#endif
}

void clComplexToArg_kernel(int noutput_items, const FComplex *in, float *out) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	#pragma acc kernels loop gang worker copyin(in[0:noutput_items]) copyout(out[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
#ifdef USE_FAST_ATAN2
		out[i] = fast_atan2f(in[i].imag,in[i].real);
#else
		out[i] = atan2(in[i].imag,in[i].real);
#endif
	}   
}
