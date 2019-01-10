#include "openacc.h"

#define OCLTYPE_GPU 1
#define OCLTYPE_ACCELERATOR 2
#define OCLTYPE_CPU 3
#define OCLTYPE_ANY 4

#define OCLDEVICESELECTOR_FIRST 1
#define OCLDEVICESELECTOR_SPECIFIC 2

void acc_initializer(acc_device_t deviceType, int devSelector, int devId) {
	acc_init(deviceType);
	if( devSelector == OCLDEVICESELECTOR_SPECIFIC ) {
		acc_set_device_num(devId, deviceType);
	}
}
