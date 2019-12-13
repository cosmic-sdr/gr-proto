#include <brisbane/brisbane_openmp.h>

static void vecadd(int* out, int* in0, int* in1, BRISBANE_OPENMP_KERNEL_ARGS) {
  size_t _id;
#pragma omp parallel for shared(out, in0, in1) private(_id)
  BRISBANE_OPENMP_KERNEL_BEGIN
  out[_id] = in0[_id] + in1[_id];
  BRISBANE_OPENMP_KERNEL_END
}

static void saxpy(int* out, int in0, int* in1, int* in2, BRISBANE_OPENMP_KERNEL_ARGS) {
  size_t _id;
#pragma omp parallel for shared(out, in0, in1, in2) private(_id)
  BRISBANE_OPENMP_KERNEL_BEGIN
  out[_id] = in0 * in1[_id] + in2[_id];
  BRISBANE_OPENMP_KERNEL_END
}

