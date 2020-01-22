/*
 * GRACCBase.h
 *
 *  Created on: Feb 9, 2017
 *      Author: root
 */

#ifndef LIB_GRACCBASE_H_
#define LIB_GRACCBASE_H_

#ifndef LIB_GRCLBASE_H_

#include "accSComplex.h"
#include "../include/openacc/api.h"

#include <boost/thread/mutex.hpp>

#define GRBUFFER_FACTOR 4

#define DTYPE_COMPLEX 1
#define DTYPE_FLOAT 2
#define DTYPE_INT 3

#define ACCTYPE_DEFAULT (1 << 0)
#define ACCTYPE_CPU (1 << 1)
#define ACCTYPE_GPU (1 << 2)
#define ACCTYPE_ACCELERATOR (1 << 3)
#define ACCTYPE_CUSTOM (1 << 4)
#define ACCTYPE_ANY 0xFFFFFFFF

#define ACCDEVICESELECTOR_FIRST 1
#define ACCDEVICESELECTOR_SPECIFIC 2

#endif

//#include "acc_helper.h"
#include "openacc.h"
#if TR_MODE == 3
extern "C" {
#include "minos.h"
}
#endif

namespace gr {
namespace openacc {

extern bool CLPRINT_NITEMS;  // Enable this in GRACCBase.cpp to print the number of items passed to the work functions if debug is enabled for the module
extern int gracc_counter;

class OPENACC_API GRACCBase {
protected:
	int threadID;
     int dataType;
	 size_t dataSize;
	int acc_init_done;

    int contextType;
    std::string platformName="";

    boost::mutex d_mutex;

	acc_device_t deviceType;
	int deviceId;

	virtual void InitOpenACC(int devType, int devId);

public:
	//static int gracc_counter;
	GRACCBase(int devType); // selects First of specified type
	GRACCBase(int devType, int devId);
	GRACCBase(int idataType, size_t dsize, int devType, int devId);
	virtual ~GRACCBase();

    int GetContextType();
};

} /* namespace openacc */
} /* namespace gr */

#endif /* LIB_GRACCBASE_H_ */
