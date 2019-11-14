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

#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3
    acc_init(deviceType);
#endif
}

void accLog_deviceData_malloc(size_t in_device_buffer_size, d_void **in_device_buffer, size_t out_device_buffer_size, d_void **out_device_buffer, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2
    HI_set_context();
#endif
    *in_device_buffer = (d_void *)acc_malloc(in_device_buffer_size);
    *out_device_buffer = (d_void *)acc_malloc(out_device_buffer_size);
}

void accLog_deviceData_free(d_void *in_device_buffer, d_void *out_device_buffer, int threadID) {
    acc_free(in_device_buffer);
    acc_free(out_device_buffer);
}

void accLog_map(int noutput_items, const float *in, d_void *in_device_buffer, float *out, d_void *out_device_buffer, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2
    HI_set_context();
#endif
    acc_map_data((h_void *)in, in_device_buffer, noutput_items*sizeof(const float));
    acc_map_data((h_void *)out, out_device_buffer, noutput_items*sizeof(float));
}

void accLog_unmap(const float *in, float *out, int threadID) {
    acc_unmap_data((h_void *)in);
    acc_unmap_data((h_void *)out);
}

void accLog_kernel( int noutput_items, float n_val, float k_val, const float * in, float * out , int threadID) {
	int i;
#ifdef GEN_ASPEN
#pragma aspen  declare param(noutput_items:__INPUTSIZE1__)
#endif

    if( acc_is_present((h_void *)in, noutput_items*sizeof(const float)) ) {
        acc_update_device((h_void *)in, noutput_items*sizeof(const float));
    }

	#pragma acc kernels loop gang worker pcopyin(in[0:noutput_items]) pcopyout(out[0:noutput_items]) 
	for( i=0; i<noutput_items; i++ ) {
		out[i] = n_val * log10(in[i]) + k_val;
	}

    if( acc_is_present((h_void *)out, noutput_items*sizeof(float)) ) {
        acc_update_self((h_void *)out, noutput_items*sizeof(float));
    }
}
