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
#include "accComplexToArg_impl.h"

namespace gr {
  namespace openacc {

    accComplexToArg::sptr
    accComplexToArg::make(int contextType, int deviceId, size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new accComplexToArg_impl(contextType, deviceId, vlen));
    }

    /*
     * The private constructor
     */
    accComplexToArg_impl::accComplexToArg_impl(int contextType, int deviceId, size_t vlen)
      : gr::sync_block("accComplexToArg",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen),
              gr::io_signature::make(1, 1, sizeof(float)*vlen)), d_vlen(vlen),
        GRACCBase(contextType, deviceId)
    {
		//if( gracc_counter <= 1 ) {
        	accComplexToArg_init(deviceType, deviceId, threadID);
		//}
		//acc_init_done = 1;
        in_device_buffer_size = 0;
        out_device_buffer_size = 0;
    }

    /*
     * Our virtual destructor.
     */
    accComplexToArg_impl::~accComplexToArg_impl()
    {
    }

    int accComplexToArg_impl::testCPU(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
        {   
        gr_complex *in = (gr_complex*)input_items[0];
        float *out = (float*)output_items[0];
		int noi = noutput_items * d_vlen;

        for(int i = 0; i < noi; i++) {
            out[i] = fast_atan2f(in[i].imag(),in[i].real());
        }   

        return noutput_items;
    }   

    int accComplexToArg_impl::testOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items) {
        return processOpenACC(noutput_items,ninput_items,input_items, output_items);
    }   

    int accComplexToArg_impl::processOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
    {
        // Protect context from switching
        gr::thread::scoped_lock guard(d_mutex);
		if( acc_init_done == 0 ) {
        	//accComplexToArg_init(deviceType, deviceId, threadID);
			in_device_buffer_size = noutput_items*d_vlen*sizeof(const FComplex)*3;
			out_device_buffer_size = noutput_items*d_vlen*sizeof(float)*3;
        	accComplexToArg_deviceData_malloc(in_device_buffer_size, (d_void **)&in_device_buffer, out_device_buffer_size, (d_void **)&out_device_buffer, threadID);
        	accComplexToArg_map(noutput_items*d_vlen, (const FComplex *)input_items[0], in_device_buffer, (float *)output_items[0], out_device_buffer, threadID);
			acc_init_done = 1;
		} else {
            if( noutput_items*d_vlen*sizeof(const FComplex) <= in_device_buffer_size ) {
        		accComplexToArg_map(noutput_items*d_vlen, (const FComplex *)input_items[0], in_device_buffer, (float *)output_items[0], out_device_buffer, threadID);
            }
        }

        // Do the work
        accComplexToArg_kernel(noutput_items*d_vlen, (const FComplex *)input_items[0], (float *)output_items[0], threadID);

        if( noutput_items*d_vlen*sizeof(const FComplex) <= in_device_buffer_size ) {
            accComplexToArg_unmap((const FComplex *)input_items[0], (float *)output_items[0], threadID);
        }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    int
    accComplexToArg_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        int retVal = processOpenACC(noutput_items,d_ninput_items,input_items,output_items);

      // Tell runtime system how many output items we produced.
      return retVal;
    }

  } /* namespace openacc */
} /* namespace gr */

