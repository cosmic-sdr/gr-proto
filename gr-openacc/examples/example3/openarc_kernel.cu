#ifndef __CUDA_KERNELHEADER__ 
#define __CUDA_KERNELHEADER__ 
/********************************************/
/* Added codes for OpenACC2CUDA translation */
/********************************************/
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
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
#ifndef DBL_MIN
#define DBL_MIN 2.2250738585072014e-308
#endif
#endif


extern "C" __global__ void accLog_kernel_kernel0(float * in1, float * out, float k_val, float n_val, int noutput_items)
{
int lwpriv__i;
lwpriv__i=(threadIdx.x+(blockIdx.x*64));
if (lwpriv__i<noutput_items)
{
out[lwpriv__i]=((n_val*log10(in1[lwpriv__i]))+k_val);
}
}

#ifndef __CUDA_KERNELHEADER__ 
#define __CUDA_KERNELHEADER__ 
/********************************************/
/* Added codes for OpenACC2CUDA translation */
/********************************************/
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
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
#ifndef DBL_MIN
#define DBL_MIN 2.2250738585072014e-308
#endif
#endif


struct FComplexStruct
{
float real;
float imag;
};

typedef struct FComplexStruct FComplex;
extern "C" __global__ void accComplexToArg_kernel_kernel0(FComplex * in, float * out, int noutput_items)
{
int lwpriv__i;
lwpriv__i=(threadIdx.x+(blockIdx.x*64));
if (lwpriv__i<noutput_items)
{
out[lwpriv__i]=atan2(in[lwpriv__i].imag, in[lwpriv__i].real);
}
}

#ifndef __CUDA_KERNELHEADER__ 
#define __CUDA_KERNELHEADER__ 
/********************************************/
/* Added codes for OpenACC2CUDA translation */
/********************************************/
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
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
#ifndef DBL_MIN
#define DBL_MIN 2.2250738585072014e-308
#endif
#endif


extern "C" __global__ void accComplexToMag_kernel_kernel0(FComplex * in, float * out, int noutput_items)
{
int lwpriv__i;
float aval;
float bval;
lwpriv__i=(threadIdx.x+(blockIdx.x*64));
if (lwpriv__i<noutput_items)
{
aval=in[lwpriv__i].imag;
bval=in[lwpriv__i].real;
out[lwpriv__i]=sqrt(((aval*aval)+(bval*bval)));
}
}

#ifndef __CUDA_KERNELHEADER__ 
#define __CUDA_KERNELHEADER__ 
/********************************************/
/* Added codes for OpenACC2CUDA translation */
/********************************************/
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
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
#ifndef DBL_MIN
#define DBL_MIN 2.2250738585072014e-308
#endif
#endif


extern "C" __global__ void accComplexToMagPhase_kernel_kernel0(FComplex * in, float * out0, float * out1, int noutput_items)
{
int lwpriv__i;
float aval;
float bval;
lwpriv__i=(threadIdx.x+(blockIdx.x*64));
if (lwpriv__i<noutput_items)
{
aval=in[lwpriv__i].imag;
bval=in[lwpriv__i].real;
out0[lwpriv__i]=sqrt(((aval*aval)+(bval*bval)));
out1[lwpriv__i]=atan2(aval, bval);
}
}

#ifndef __CUDA_KERNELHEADER__ 
#define __CUDA_KERNELHEADER__ 
/********************************************/
/* Added codes for OpenACC2CUDA translation */
/********************************************/
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
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
#ifndef DBL_MIN
#define DBL_MIN 2.2250738585072014e-308
#endif
#endif


extern "C" __global__ void accComplexToMagSquared_kernel_kernel0(FComplex * in, float * out, int noutput_items)
{
int lwpriv__i;
float aval;
float bval;
lwpriv__i=(threadIdx.x+(blockIdx.x*64));
if (lwpriv__i<noutput_items)
{
aval=in[lwpriv__i].imag;
bval=in[lwpriv__i].real;
out[lwpriv__i]=((aval*aval)+(bval*bval));
}
}

#ifndef __CUDA_KERNELHEADER__ 
#define __CUDA_KERNELHEADER__ 
/********************************************/
/* Added codes for OpenACC2CUDA translation */
/********************************************/
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
#ifndef DBL_MAX
#define DBL_MAX 1.7976931348623158e+308
#endif
#ifndef DBL_MIN
#define DBL_MIN 2.2250738585072014e-308
#endif
#endif


extern "C" __global__ void accMagPhaseToComplex_kernel_kernel0(float * a, float * b, FComplex * c, int noutput_items)
{
int lwpriv__i;
float mag;
float phase;
float real;
float imag;
lwpriv__i=(threadIdx.x+(blockIdx.x*64));
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

