#include "clComplexToArg_kernel.h"

#ifdef _OPENARC_
#include "math.h"
#include "fast_atan2f.c"
#endif

void clComplexToArg_kernel(int noutput_items, const FComplex *in, float *out) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#pragma aspen  declare param(aspen_param_sizeof_FComplex:8)
#endif

	#pragma acc kernels loop gang worker copyin(in[0:noutput_items]) copyout(out[0:noutput_items]) 
	for(i = 0; i < noutput_items; i++) {
		out[i] = fast_atan2f(in[i].imag,in[i].real);
	}   
}
