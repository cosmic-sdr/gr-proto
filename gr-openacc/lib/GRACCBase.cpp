/*
 * GRACCBase.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: root
 */

#include <iostream>

#include "GRACCBase.h"

namespace gr {
namespace openacc {

#ifdef GRACC_ONLY
bool CLPRINT_NITEMS=false;
#endif

void GRACCBase::InitOpenACC(int devType, int devId) {

	switch(devType) {
	case ACCTYPE_CPU:
		contextType = ACCTYPE_CPU;
		deviceType = acc_device_host;
		platformName = "CPU";
		break;
	case ACCTYPE_ACCELERATOR:
		contextType = ACCTYPE_ACCELERATOR;
		deviceType = acc_device_not_host;
		platformName = "ACCELERATOR";
		break;
	case ACCTYPE_ANY:
		contextType = ACCTYPE_ANY;
		deviceType = acc_device_default;
		platformName = "DEFAULT DEVICE";
		break;
	default:
		contextType = ACCTYPE_ACCELERATOR;
		deviceType = acc_device_gpu;
		platformName = "GPU";
	}
}

GRACCBase::GRACCBase(int idataType, size_t dsize, int devType, int devId) {
	dataType = idataType;
	dataSize = dsize;
	InitOpenACC(devType,devId);
}

GRACCBase::GRACCBase(int devType, int devId) {
	InitOpenACC(devType,devId);
}

GRACCBase::GRACCBase(int devType) {
	InitOpenACC(devType,0);
}

int GRACCBase::GetContextType() {
    return contextType;
}

GRACCBase::~GRACCBase() {
#if !defined(TR_MODE) || TR_MODE == 0
	acc_shutdown(deviceType);
#elif TR_MODE == 3
	mcl_finit();
#endif
}

} /* namespace openacc */
} /* namespace gr */
