#ifndef INCLUDED_CLENABLED_CLMAGPHASETOCOMPLEX_KERNEL_H
#define INCLUDED_CLENABLED_CLMAGPHASETOCOMPLEX_KERNEL_H

struct FComplexStruct {
	float real;
	float imag;
};

typedef struct FComplexStruct FComplex;

void clMagPhaseToComplex_kernel(int noutput_items, const float *a, const float *b, FComplex *c);

#endif
