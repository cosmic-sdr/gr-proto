#include "clComplexToArg_kernel.h"

float fast_atan2f(float y, float x);

void clComplexToArg_kernel(int noutput_items, const FComplex *in, float *out) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#endif

	#pragma acc kernels loop gang worker copyin(in[0:noutput_items]) copyout(out[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
		out[i] = fast_atan2f(in[i].imag,in[i].real);
	}   
}
