#include "accComplexToMagPhase_kernel.h"

#include "math.h"
#ifdef USE_FAST_ATAN2
#include "fast_atan2f.c"
#endif

void accComplexToMagPhase_init(acc_device_t deviceType, int devId) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3
    acc_init(deviceType);
#endif
}

void accComplexToMagPhase_kernel(int noutput_items, const FComplex *in, float *out0, float *out1) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	#pragma acc kernels loop gang worker copyin(in[0:noutput_items]) copyout(out0[0:noutput_items], out1[0:noutput_items]) 
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
}
