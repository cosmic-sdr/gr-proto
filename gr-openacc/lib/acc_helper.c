#include "openacc.h"

#define ACCTYPE_GPU 1
#define ACCTYPE_ACCELERATOR 2
#define ACCTYPE_CPU 3
#define ACCTYPE_ANY 4

#define ACCDEVICESELECTOR_FIRST 1
#define ACCDEVICESELECTOR_SPECIFIC 2

void gracc_init(acc_device_t deviceType, int devId, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 3 || TR_MODE == 4
    acc_init(deviceType);
#endif
}

void gracc_pcopyin(h_void* hostPtr, size_t size, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
	acc_pcopyin(hostPtr, size);
}

void gracc_pcreate(h_void* hostPtr, size_t size, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
	acc_pcreate(hostPtr, size);
}

void gracc_update_device(h_void* hostPtr, size_t size, int threadID) {
	acc_update_device(hostPtr, size);
}

void gracc_update_self(h_void* hostPtr, size_t size, int threadID) {
	acc_update_self(hostPtr, size);
}

void gracc_map_data(h_void* hostPtr, d_void* devPtr, size_t size, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
	acc_map_data(hostPtr, devPtr, size);
}

void gracc_unmap_data(h_void* hostPtr, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
	acc_unmap_data(hostPtr);
}
