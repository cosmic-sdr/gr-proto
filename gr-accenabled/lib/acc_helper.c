#include "openacc.h"

#define OCLTYPE_GPU 1
#define OCLTYPE_ACCELERATOR 2
#define OCLTYPE_CPU 3
#define OCLTYPE_ANY 4

#define OCLDEVICESELECTOR_FIRST 1
#define OCLDEVICESELECTOR_SPECIFIC 2

void acc_initializer(int openCLPlatformType, int devSelector, int platformId, int devId) {
acc_device_t deviceType;
	switch(openCLPlatformType) {
	case OCLTYPE_CPU:
		deviceType=acc_device_host;
		break;
	case OCLTYPE_ACCELERATOR:
		deviceType=acc_device_not_host;
		break;
	case OCLTYPE_ANY:
		deviceType=acc_device_default;
		break;
	default:
		deviceType=acc_device_gpu;
	}
	acc_init(deviceType);

	//[DEBUG] platformId is ignored for now.
	
	if( devSelector == OCLDEVICESELECTOR_SPECIFIC ) {
		acc_set_device_num(devId, deviceType);
	}
}
