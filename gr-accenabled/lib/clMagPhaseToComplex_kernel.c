#include "clMagPhaseToComplex_kernel.h"

#include "math.h"

void clMagPhaseToComplex_init(acc_device_t deviceType, int devSelector, int devId) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3
    acc_init(deviceType);
#if !defined(TR_MODE) || TR_MODE == 0 
    if( devSelector == OCLDEVICESELECTOR_SPECIFIC ) { 
        acc_set_device_num(devId, deviceType);
    }   
#endif
#endif
}


void clMagPhaseToComplex_kernel(int noutput_items, const float *a, const float *b, FComplex *c) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	#pragma acc kernels loop gang worker copyin(a[0:noutput_items], b[0:noutput_items]) copyout(c[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
		float mag = a[i];
		float phase = b[i];
		float real = mag*cos(phase);
		float imag = mag*sin(phase);
		c[i].real = real;
		c[i].imag = imag;
	}   
}
