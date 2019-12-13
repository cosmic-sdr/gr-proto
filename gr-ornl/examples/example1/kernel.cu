extern "C" __global__ void vecadd(int* out, int* in0, int* in1, size_t blockOff_x) {
  size_t id = (blockOff_x + blockIdx.x) * blockDim.x + threadIdx.x;
  out[id] = in0[id] + in1[id];
}

extern "C" __global__ void saxpy(int* out, int in0, int* in1, int* in2, size_t blockOff_x) {
  size_t id = (blockOff_x + blockIdx.x) * blockDim.x + threadIdx.x;
  out[id] = in0 * in1[id] + in2[id];
}

