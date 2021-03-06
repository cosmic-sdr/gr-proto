/* -*- c++ -*- */
/* 
 * Copyright 2019 Seyong Lee.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "accLog_impl.h"

namespace gr {
  namespace openacc {

    accLog::sptr
    accLog::make(int contextType, int deviceId, float nValue, float kValue, size_t vlen, int copy_in, int copy_out)
    {
      return gnuradio::get_initial_sptr
        (new accLog_impl(contextType, deviceId, nValue, kValue, vlen, copy_in, copy_out));
    }

    /*
     * The private constructor
     */
    accLog_impl::accLog_impl(int contextType, int deviceId, float nValue, float kValue, size_t vlen, int copy_in, int copy_out)
      : gr::sync_block("accLog",
              gr::io_signature::make(1, 1, sizeof(float)*vlen),
              gr::io_signature::make(1, 1, sizeof(float)*vlen)), d_vlen(vlen), gracc_copy_in(copy_in), gracc_copy_out(copy_out),
        GRACCBase(contextType, deviceId)
    {
		//if( gracc_counter <= 1 ) {
        	accLog_init(deviceType, deviceId, threadID);
		//}
		//acc_init_done = 1;
        n_val = nValue;
        k_val = kValue;
    }

    /*
     * Our virtual destructor.
     */
    accLog_impl::~accLog_impl()
    {
    }

    int accLog_impl::testCPU(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
        {

        const float *in1 = (const float *) input_items[0];
        float *out = (float *) output_items[0];
        int noi = noutput_items * d_vlen;

        for (int i=0;i<noi;i++) {
            out[i] = n_val * log10(in1[i]) + k_val;
        }

        return noutput_items;
    }

    int accLog_impl::testOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items) {
        return processOpenACC(noutput_items,ninput_items,input_items, output_items);
    }

    int accLog_impl::processOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
    {
        // Protect context from switching
        gr::thread::scoped_lock guard(d_mutex);
		int max_noutputs = max_noutput_items();
		if( acc_init_done == 0 ) {
        	//accLog_init(deviceType, deviceId, threadID);
			if( max_noutputs == 0 ) {
				printf("[ERROR in accLog] max_noutput_items() is NOT set properly; exit!\n");
				exit(EXIT_FAILURE);
			}
			if( gracc_copy_in == 1 ) {
				gracc_copyin((h_void*)input_items[0], GRBUFFER_FACTOR*max_noutputs*sizeof(const float), threadID);
			}
			gracc_create((h_void*)output_items[0], GRBUFFER_FACTOR*max_noutputs*sizeof(float),  threadID);
            acc_init_done = 1;
		} else if( gracc_copy_in == 1 ) {
			gracc_update_device((h_void*)input_items[0], noutput_items*sizeof(const float),  threadID);
        }

        // Do the work
        accLog_kernel(noutput_items*d_vlen, n_val, k_val, (const float *)input_items[0], (float *)output_items[0], threadID);

        if( gracc_copy_out == 1 ) {
			gracc_update_self((h_void*)output_items[0], noutput_items*sizeof(float),  threadID);
        }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    int
    accLog_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      // Do <+signal processing+>
      int retVal; 
      if( contextType == ACCTYPE_CPU ) {
      	retVal = testCPU(noutput_items,d_ninput_items,input_items,output_items);
      } else {
      	retVal = processOpenACC(noutput_items,d_ninput_items,input_items,output_items);
      }

      // Tell runtime system how many output items we produced.
      return retVal;
    }

  } /* namespace openacc */
} /* namespace gr */

