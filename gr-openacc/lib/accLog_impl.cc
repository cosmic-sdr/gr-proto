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
    accLog::make(int contextType, int deviceId, float nValue, float kValue, size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new accLog_impl(contextType, deviceId, nValue, kValue, vlen));
    }

    /*
     * The private constructor
     */
    accLog_impl::accLog_impl(int contextType, int deviceId, float nValue, float kValue, size_t vlen)
      : gr::sync_block("accLog",
              gr::io_signature::make(1, 1, sizeof(float)*vlen),
              gr::io_signature::make(1, 1, sizeof(float)*vlen)), d_vlen(vlen),
        GRACCBase(contextType, deviceId)
    {
		//if( gracc_counter <= 1 ) {
        	accLog_init(deviceType, deviceId, threadID);
		//}
		acc_init_done = 1;
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
		if( acc_init_done == 0 ) {
        	accLog_init(deviceType, deviceId, threadID);
			acc_init_done = 1;
		}

        // Do the work
        accLog_kernel(noutput_items*d_vlen, n_val, k_val, (const float *)input_items[0], (float *)output_items[0], threadID);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    int
    accLog_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      // Do <+signal processing+>
      int retVal = processOpenACC(noutput_items,d_ninput_items,input_items,output_items);

      // Tell runtime system how many output items we produced.
      return retVal;
    }

  } /* namespace openacc */
} /* namespace gr */

