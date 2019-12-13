#include <brisbane/brisbane_openmp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  __global int * out;
  __global int * in0;
  __global int * in1;
} brisbane_openmp_vecadd_args;
brisbane_openmp_vecadd_args vecadd_args;

typedef struct {
  __global int * out;
  int in0;
  __global int * in1;
  __global int * in2;
} brisbane_openmp_saxpy_args;
brisbane_openmp_saxpy_args saxpy_args;

static int brisbane_openmp_vecadd_setarg(int idx, size_t size, void* value) {
  switch (idx) {
    default: return BRISBANE_ERR;
  }
  return BRISBANE_OK;
}

static int brisbane_openmp_saxpy_setarg(int idx, size_t size, void* value) {
  switch (idx) {
    case 1: memcpy(&saxpy_args.in0, value, size); break;
    default: return BRISBANE_ERR;
  }
  return BRISBANE_OK;
}

static int brisbane_openmp_vecadd_setmem(int idx, void* mem) {
  switch (idx) {
    case 0: vecadd_args.out = (__global int *__restrict) mem; break;
    case 1: vecadd_args.in0 = (__global int *__restrict) mem; break;
    case 2: vecadd_args.in1 = (__global int *__restrict) mem; break;
    default: return BRISBANE_ERR;
  }
  return BRISBANE_OK;
}

static int brisbane_openmp_saxpy_setmem(int idx, void* mem) {
  switch (idx) {
    case 0: saxpy_args.out = (__global int *__restrict) mem; break;
    case 2: saxpy_args.in1 = (__global int *__restrict) mem; break;
    case 3: saxpy_args.in2 = (__global int *__restrict) mem; break;
    default: return BRISBANE_ERR;
  }
  return BRISBANE_OK;
}

#include "kernel.cl.openmp.h"

int brisbane_openmp_kernel(const char* name) {
  brisbane_openmp_lock();
  if (strcmp(name, "vecadd") == 0) {
    brisbane_openmp_kernel_idx = 0;
    return BRISBANE_OK;
  }
  if (strcmp(name, "saxpy") == 0) {
    brisbane_openmp_kernel_idx = 1;
    return BRISBANE_OK;
  }
  return BRISBANE_ERR;
}

int brisbane_openmp_setarg(int idx, size_t size, void* value) {
  switch (brisbane_openmp_kernel_idx) {
    case 0: return brisbane_openmp_vecadd_setarg(idx, size, value);
    case 1: return brisbane_openmp_saxpy_setarg(idx, size, value);
  }
  return BRISBANE_ERR;
}

int brisbane_openmp_setmem(int idx, void* mem) {
  switch (brisbane_openmp_kernel_idx) {
    case 0: return brisbane_openmp_vecadd_setmem(idx, mem);
    case 1: return brisbane_openmp_saxpy_setmem(idx, mem);
  }
  return BRISBANE_ERR;
}

int brisbane_openmp_launch(int dim, size_t off, size_t ndr) {
  switch (brisbane_openmp_kernel_idx) {
    case 0: vecadd(vecadd_args.out, vecadd_args.in0, vecadd_args.in1, off, ndr); break;
    case 1: saxpy(saxpy_args.out, saxpy_args.in0, saxpy_args.in1, saxpy_args.in2, off, ndr); break;
  }
  brisbane_openmp_unlock();
  return BRISBANE_OK;
}

#ifdef __cplusplus
} /* end of extern "C" */
#endif

