#include "clLog_kernel.h"

void clLog_init(acc_device_t deviceType, int devSelector, int devId) {
#if !defined(TR_MODE) || TR_MODE == 0
    acc_init(deviceType);
    if( devSelector == OCLDEVICESELECTOR_SPECIFIC ) { 
        acc_set_device_num(devId, deviceType);
    }   
#endif
}


void clLog_kernel( int noutput_items, float n_val, float k_val, unsigned int localWGSize, const float * in1, float * out ) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#endif

	#pragma acc kernels loop gang worker copyin(in1[0:noutput_items]) copyout(out[0:noutput_items]) 
	for( i=0; i<noutput_items; i++ ) {
		out[i] = n_val * log10(in1[i]) + k_val;
	}
}
