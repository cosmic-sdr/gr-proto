#include "accLog_kernel.h"
#ifdef DEBUG_ON
#include "stdio.h"
#endif

void accLog_init(acc_device_t deviceType, int devId, int threadID) {
#ifdef DEBUG_ON
    switch(deviceType) {
    case acc_device_gpu:
        printf("OpenACC Context: acc_device_gpu\n");
    break;
    case acc_device_host:
        printf("OpenACC Context: acc_device_cpu\n");
    break;
    case acc_device_not_host:
        printf("OpenACC Context: acc_device_not_host\n");
    break;
    case acc_device_default:
        printf("OpenACC Context: acc_device_not_default\n");
    break;
	default: 
        printf("OpenACC Context: unknown type (%d)\n", deviceType);
    }
#endif

#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3 || TR_MODE == 4
    acc_init(deviceType);
#endif
}

void accLog_kernel( int noutput_items, float n_val, float k_val, const float * in, float * out , int threadID) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#endif

	#pragma acc kernels loop gang worker present(in[0:noutput_items]) present(out[0:noutput_items]) 
	for( i=0; i<noutput_items; i++ ) {
		out[i] = n_val * log10(in[i]) + k_val;
	}
}
