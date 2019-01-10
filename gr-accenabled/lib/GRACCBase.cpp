/*
 * GRACCBase.cpp
 *
 *  Created on: Feb 9, 2017
 *      Author: root
 */

#include <iostream>

#include "GRACCBase.h"

namespace gr {
namespace clenabled {

#ifdef GRACC_ONLY
bool CLPRINT_NITEMS=false;
#endif

void GRACCBase::InitOpenACC(int openCLPlatformType, int devSelector,int platformId, int devId, bool setDebug) {

	debugMode=setDebug;
	switch(openCLPlatformType) {
	case OCLTYPE_CPU:
		contextType = CL_DEVICE_TYPE_CPU;
		deviceType = acc_device_host;
		break;
	case OCLTYPE_ACCELERATOR:
		contextType = CL_DEVICE_TYPE_ACCELERATOR;
		deviceType = acc_device_not_host;
		break;
	case OCLTYPE_ANY:
		contextType = CL_DEVICE_TYPE_ALL;
		deviceType = acc_device_default;
		break;
	default:
		contextType = CL_DEVICE_TYPE_ACCELERATOR;
		deviceType = acc_device_gpu;
	}
	acc_initializer(deviceType, devSelector, devId); 
}

GRACCBase::GRACCBase(int openCLPlatformType, int devSelector,int platformId, int devId, bool setDebug) {
	InitOpenACC(openCLPlatformType,devSelector,platformId,devId,setDebug);
}

GRACCBase::GRACCBase(int openCLPlatformType, bool setDebug) {
	InitOpenACC(openCLPlatformType,OCLDEVICESELECTOR_FIRST,0,0,setDebug);
}

cl_device_type GRACCBase::GetContextType() {
	return contextType;
}

void GRACCBase::cleanup() {
	acc_shutdown(deviceType);
}

GRACCBase::~GRACCBase() {
}

bool GRACCBase::stop() {
	cleanup();

	return true;
}

} /* namespace clenabled */
} /* namespace gr */
