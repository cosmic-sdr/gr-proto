#include <math.h>

void log_kernel( int noutput_items, float n_val, float k_val, unsigned int localWGSize, const float * in1, float * out ) {
	int i;
	#pragma acc kernels loop gang worker copyin(in1[0:noutput_items]) copyout(out[0:noutput_items]) 
	for( i=0; i<noutput_items; i++ ) {
		out[i] = n_val * log10(in1[i]) + k_val;
	}
}
