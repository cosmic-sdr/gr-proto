#include "openacc.h"

#define ACCTYPE_GPU 1
#define ACCTYPE_ACCELERATOR 2
#define ACCTYPE_CPU 3
#define ACCTYPE_ANY 4

#define ACCDEVICESELECTOR_FIRST 1
#define ACCDEVICESELECTOR_SPECIFIC 2

void acc_initializer(acc_device_t deviceType, int devId) {
	acc_init(deviceType);
}
