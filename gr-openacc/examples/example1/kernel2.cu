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


extern "C" __global__ void accLog_kernel_kernel0(float * in, float * out, float k_val, float n_val, int noutput_items)
{
int lwpriv__i;
lwpriv__i=(threadIdx.x+(blockIdx.x*64));
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
__device__ static float dev__fast_atan2f_GP0_TU0_CT0(float y, float x, float fast_atan_table[])
{
float x_abs;
float y_abs;
float z;
float alpha;
float angle;
float base_angle;
int index;
/* normalize to +- 45 degree range */
float _ret_val_0;
y_abs=fabsf(y);
x_abs=fabsf(x);
/* don't divide by zero! */
if ( ! ((y_abs>0.0F)||(x_abs>0.0F)))
{
_ret_val_0=0.0;
return _ret_val_0;
}
if (y_abs<x_abs)
{
z=(y_abs/x_abs);
}
else
{
z=(x_abs/y_abs);
}
/* when ratio approaches the table resolution, the angle is */
/* best approximated with the argument itself... */
/* (smallest non-zero value in table) */
if (z<0.003921569)
{
base_angle=z;
}
else
{
/* find index and interpolation value */
alpha=(z*((float)255));
index=(((int)alpha)&0xff);
alpha-=((float)index);
/* determine base angle based on quadrant and */
/* add or subtract table value from base angle based on quadrant */
base_angle=fast_atan_table[index];
base_angle+=((fast_atan_table[(index+1)]-fast_atan_table[index])*alpha);
}
if (x_abs>y_abs)
{
/* -45 -> 45 or 135 -> 225 */
if (x>=0.0)
{
/* -45 -> 45 */
/* 0 -> 45, angle OK */
if (y>=0.0)
{
angle=base_angle;
}
else
{
angle=( - base_angle);
}
/* -45 -> 0, angle = -angle */
}
else
{
/* 135 -> 180 or 180 -> -135 */
angle=3.141592653589793;
/* 135 -> 180, angle = 180 - angle */
if (y>=0.0)
{
angle-=base_angle;
}
else
{
angle=(base_angle-angle);
}
/* 180 -> -135, angle = angle - 180 */
}
}
else
{
/* 45 -> 135 or -135 -> -45 */
if (y>=0.0)
{
/* 45 -> 135 */
angle=1.5707963267948966;
/* 45 -> 90, angle = 90 - angle */
if (x>=0.0)
{
angle-=base_angle;
}
else
{
angle+=base_angle;
}
/* 90 -> 135, angle = 90 + angle */
}
else
{
/* -135 -> -45 */
angle=( - 1.5707963267948966);
/* -90 -> -45, angle = -90 + angle */
if (x>=0.0)
{
angle+=base_angle;
}
else
{
angle-=base_angle;
}
/* -135 -> -90, angle = -90 - angle */
}
}
return angle;
}

extern "C" __global__ void accComplexToArg_kernel_kernel0(FComplex * in, float * out, float fast_atan_table[], int noutput_items)
{
int lwpriv__i;
lwpriv__i=(threadIdx.x+(blockIdx.x*64));
if (lwpriv__i<noutput_items)
{
out[lwpriv__i]=dev__fast_atan2f_GP0_TU0_CT0(in[lwpriv__i].imag, in[lwpriv__i].real, fast_atan_table);
}
}

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

extern "C" __global__ void accComplexToMagPhase_kernel_kernel0(FComplex * in, float * out0, float * out1, float fast_atan_table[], int noutput_items)
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
out1[lwpriv__i]=dev__fast_atan2f_GP0_TU0_CT0(aval, bval, fast_atan_table);
}
}

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

