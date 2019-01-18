#ifndef INCLUDED_CLENABLED_CLCOMPLEXTOARG_KERNEL_H
#define INCLUDED_CLENABLED_CLCOMPLEXTOARG_KERNEL_H

#include "fast_atan2f.h"

struct ComplexStruct {
	float real;
	float imag;
};

typedef struct ComplexStruct SComplex;

void clComplexToArg_kernel(int noutput_items, const SComplex *in, float *out);

#endif
