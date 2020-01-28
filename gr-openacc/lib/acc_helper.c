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

void gracc_copyin(h_void* hostPtr, size_t size, int threadID) {
	d_void* devPtr;
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
#if !defined(TR_MODE) ||  TR_MODE != 1
	devPtr = acc_malloc(size);
	acc_map_data_forced(hostPtr, devPtr, size);
	acc_update_device(hostPtr, size);
#endif
}

void gracc_create(h_void* hostPtr, size_t size, int threadID) {
	d_void* devPtr;
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
#if !defined(TR_MODE) ||  TR_MODE != 1
	devPtr = acc_malloc(size);
	acc_map_data_forced(hostPtr, devPtr, size);
#endif
}

void gracc_pcopyin(h_void* hostPtr, size_t size, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
#if !defined(TR_MODE) ||  TR_MODE != 1
	acc_pcopyin(hostPtr, size);
#endif
}

void gracc_pcreate(h_void* hostPtr, size_t size, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
#if !defined(TR_MODE) ||  TR_MODE != 1
	acc_pcreate(hostPtr, size);
#endif
}

void gracc_update_device(h_void* hostPtr, size_t size, int threadID) {
#if !defined(TR_MODE) ||  TR_MODE != 1
	acc_update_device(hostPtr, size);
#endif
}

void gracc_update_self(h_void* hostPtr, size_t size, int threadID) {
#if !defined(TR_MODE) ||  TR_MODE != 1
	acc_update_self(hostPtr, size);
#endif
}

void gracc_map_data(h_void* hostPtr, d_void* devPtr, size_t size, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
#if !defined(TR_MODE) ||  TR_MODE != 1
	acc_map_data(hostPtr, devPtr, size);
#endif
}

void gracc_unmap_data(h_void* hostPtr, int threadID) {
#if !defined(TR_MODE) || TR_MODE == 0 || TR_MODE == 2 || TR_MODE == 4
    HI_set_context();
#endif
#if !defined(TR_MODE) ||  TR_MODE != 1
	acc_unmap_data(hostPtr);
#endif
}
