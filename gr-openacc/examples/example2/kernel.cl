#ifndef __OpenCL_KERNELHEADER__ 
#define __OpenCL_KERNELHEADER__ 
/**********************************************/
/* Added codes for OpenACC2OpenCL translation */
/**********************************************/
#ifdef __cplusplus
#define restrict __restrict__
#endif
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#ifndef FLT_MAX
#define FLT_MAX 3.402823466e+38
#endif
#ifndef FLT_MIN
#define FLT_MIN 1.175494351e-38
#endif
#pragma OPENCL EXTENSION cl_khr_fp64: enable
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
#ifndef DBL_MIN
#define DBL_MIN 2.2250738585072014e-308
#endif
#endif


__kernel void __attribute__((reqd_work_group_size(64, 1, 1))) accLog_kernel_kernel0(__global float * in, __global float * out, float k_val, float n_val, int noutput_items)
{
int lwpriv__i;
lwpriv__i=get_global_id(0);
if (lwpriv__i<noutput_items)
{
out[lwpriv__i]=((n_val*log10(in[lwpriv__i]))+k_val);
}
}

struct FComplexStruct
{
float real;
float imag;
};

typedef struct FComplexStruct FComplex;
__kernel void __attribute__((reqd_work_group_size(64, 1, 1))) accComplexToArg_kernel_kernel0(__global FComplex * in, __global float * out, int noutput_items)
{
int lwpriv__i;
lwpriv__i=get_global_id(0);
if (lwpriv__i<noutput_items)
{
out[lwpriv__i]=atan2(in[lwpriv__i].imag, in[lwpriv__i].real);
}
}

__kernel void __attribute__((reqd_work_group_size(64, 1, 1))) accComplexToMag_kernel_kernel0(__global FComplex * in, __global float * out, int noutput_items)
{
int lwpriv__i;
float aval;
float bval;
lwpriv__i=get_global_id(0);
if (lwpriv__i<noutput_items)
{
aval=in[lwpriv__i].imag;
bval=in[lwpriv__i].real;
out[lwpriv__i]=sqrt(((aval*aval)+(bval*bval)));
}
}

__kernel void __attribute__((reqd_work_group_size(64, 1, 1))) accComplexToMagPhase_kernel_kernel0(__global FComplex * in, __global float * out0, __global float * out1, int noutput_items)
{
int lwpriv__i;
float aval;
float bval;
lwpriv__i=get_global_id(0);
if (lwpriv__i<noutput_items)
{
aval=in[lwpriv__i].imag;
bval=in[lwpriv__i].real;
out0[lwpriv__i]=sqrt(((aval*aval)+(bval*bval)));
out1[lwpriv__i]=atan2(aval, bval);
}
}

__kernel void __attribute__((reqd_work_group_size(64, 1, 1))) accComplexToMagSquared_kernel_kernel0(__global FComplex * in, __global float * out, int noutput_items)
{
int lwpriv__i;
float aval;
float bval;
lwpriv__i=get_global_id(0);
if (lwpriv__i<noutput_items)
{
aval=in[lwpriv__i].imag;
bval=in[lwpriv__i].real;
out[lwpriv__i]=((aval*aval)+(bval*bval));
}
}

__kernel void __attribute__((reqd_work_group_size(64, 1, 1))) accMagPhaseToComplex_kernel_kernel0(__global float * a, __global float * b, __global FComplex * c, int noutput_items)
{
int lwpriv__i;
float mag;
float phase;
float real;
float imag;
lwpriv__i=get_global_id(0);
if (lwpriv__i<noutput_items)
{
mag=a[lwpriv__i];
phase=b[lwpriv__i];
real=mag*cos(phase);
imag=mag*sin(phase);
c[lwpriv__i].real=real;
c[lwpriv__i].imag=imag;
}
}

