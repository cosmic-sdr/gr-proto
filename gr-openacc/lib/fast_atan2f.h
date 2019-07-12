/*
 * fast_atan2f.h
 *
 *  Created on: Feb 19, 2017
 *      Author: mpiscopo
 */

#ifndef LIB_FAST_ATAN2F_H_
#define LIB_FAST_ATAN2F_H_

#include "../include/openacc/api.h"
namespace gr {
  namespace openacc {
OPENACC_API float fast_atan2f(float y, float x);
  }
}


#endif /* LIB_FAST_ATAN2F_H_ */
