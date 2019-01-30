#ifndef INCLUDED_CLENABLED_CLCOMPLEXTOMAGPHASE_KERNEL_H
#define INCLUDED_CLENABLED_CLCOMPLEXTOMAGPHASE_KERNEL_H

struct FComplexStruct {
	float real;
	float imag;
};

typedef struct FComplexStruct FComplex;

void clComplexToArg_kernel(int noutput_items, const FComplex *in, float *out0, float *out1);

#endif
