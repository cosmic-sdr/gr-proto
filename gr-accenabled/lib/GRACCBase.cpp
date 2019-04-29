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
		//contextType = CL_DEVICE_TYPE_CPU;
		contextType = OCLTYPE_CPU;
		deviceType = acc_device_host;
		platformName = "CPU";
		break;
	case OCLTYPE_ACCELERATOR:
		//contextType = CL_DEVICE_TYPE_ACCELERATOR;
		contextType = OCLTYPE_ACCELERATOR;
		deviceType = acc_device_not_host;
		platformName = "ACCELERATOR";
		break;
	case OCLTYPE_ANY:
		//contextType = CL_DEVICE_TYPE_ALL;
		contextType = OCLTYPE_ANY;
		deviceType = acc_device_default;
		platformName = "DEFAULT DEVICE";
		break;
	default:
		//contextType = CL_DEVICE_TYPE_ACCELERATOR;
		contextType = OCLTYPE_ACCELERATOR;
		deviceType = acc_device_gpu;
		platformName = "GPU";
	}
	//acc_initializer(deviceType, devSelector, devId); 
}

GRACCBase::GRACCBase(int idataType, size_t dsize, int openCLPlatformType, int devSelector,int platformId, int devId, bool setDebug) {
	dataType = idataType;
	dataSize = dsize;
	InitOpenACC(openCLPlatformType,devSelector,platformId,devId,setDebug);
}

GRACCBase::GRACCBase(int openCLPlatformType, int devSelector,int platformId, int devId, bool setDebug) {
	InitOpenACC(openCLPlatformType,devSelector,platformId,devId,setDebug);
}

GRACCBase::GRACCBase(int openCLPlatformType, bool setDebug) {
	InitOpenACC(openCLPlatformType,OCLDEVICESELECTOR_FIRST,0,0,setDebug);
}

//cl_device_type GRACCBase::GetContextType() {
int GRACCBase::GetContextType() {
	return contextType;
}

void GRACCBase::cleanup() {
	//acc_shutdown(deviceType);
}

GRACCBase::~GRACCBase() {
#if !defined(TR_MODE) || TR_MODE == 0
	acc_shutdown(deviceType);
#elif TR_MODE == 3
	mcl_finit();
#endif
}

bool GRACCBase::stop() {
	cleanup();

	return true;
}

} /* namespace clenabled */
} /* namespace gr */
