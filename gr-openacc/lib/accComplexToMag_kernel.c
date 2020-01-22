#include "accComplexToMag_kernel.h"

#ifdef _OPENARC_
#include "math.h"
#endif

void accComplexToMag_init(acc_device_t deviceType, int devId, int threadID) {
#ifdef DEBUG_PRINT
	fprintf(stderr, "Thread %d initializes the accComplexToMag block!\n", threadID);
#endif
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3 || TR_MODE == 4
    acc_init(deviceType);
#endif
}

void accComplexToMag_kernel(int noutput_items, const FComplex *in, float *out, int threadID) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	#pragma acc kernels loop gang worker present(in[0:noutput_items]) present(out[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
		float aval = in[i].imag;
		float bval = in[i].real;
		out[i] = sqrt(aval*aval+bval*bval);
	}   
}

