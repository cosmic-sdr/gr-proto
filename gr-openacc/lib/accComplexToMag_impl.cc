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
#include "accComplexToMag_impl.h"
#include <volk/volk.h>

namespace gr {
  namespace openacc {

    accComplexToMag::sptr
    accComplexToMag::make(int contextType, int deviceId, size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new accComplexToMag_impl(contextType, deviceId, vlen));
    }

    /*
     * The private constructor
     */
    accComplexToMag_impl::accComplexToMag_impl(int contextType, int deviceId, size_t vlen)
      : gr::sync_block("accComplexToMag",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen),
              gr::io_signature::make(1, 1, sizeof(float)*vlen)), d_vlen(vlen),
        GRACCBase(contextType, deviceId)
    {
        const int alignment_multiple =
        volk_get_alignment() / sizeof(float);
        set_alignment(std::max(1,alignment_multiple));
		//if( gracc_counter <= 1 ) {
        	accComplexToMag_init(deviceType, deviceId, threadID);
		//}
		//acc_init_done = 1;
        in_device_buffer_size = 0;
        out_device_buffer_size = 0;
    }

    /*
     * Our virtual destructor.
     */
    accComplexToMag_impl::~accComplexToMag_impl()
    {
    }

    int accComplexToMag_impl::testCPU(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
        {   
        const gr_complex *in = (const gr_complex*)input_items[0];
        float *out = (float*)output_items[0];
        int noi = noutput_items * d_vlen;
/*
 *         for(int i = 0; i < noi; i++) {
 *                     out[i] = sqrt(in[i].imag()*in[i].imag()+in[i].real()*in[i].real());
 *                             }
 *                             */
        volk_32fc_magnitude_32f_u(out, in, noi);

        return noutput_items;
    }   

    int accComplexToMag_impl::testOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items) {
        return processOpenACC(noutput_items,ninput_items,input_items, output_items);
    }   

    int accComplexToMag_impl::processOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
    {
        // Protect context from switching
        gr::thread::scoped_lock guard(d_mutex);
		if( acc_init_done == 0 ) {
        	//accComplexToMag_init(deviceType, deviceId, threadID);
			//[DEBUG] We cannot use preallocated device memory since the size and start address of the input buffer can change per invocation.
        	//accComplexToMag_deviceData_alloc(noutput_items*d_vlen, (const FComplex *)input_items[0], (float *)output_items[0], threadID);
			in_device_buffer_size = noutput_items*d_vlen*sizeof(const FComplex)*3;
			out_device_buffer_size = noutput_items*d_vlen*sizeof(float)*3;
			accComplexToMag_deviceData_malloc(in_device_buffer_size, (d_void **)&in_device_buffer, out_device_buffer_size, (d_void **)&out_device_buffer, threadID);
            accComplexToMag_map(noutput_items*d_vlen, (const FComplex *)input_items[0], in_device_buffer, (float *)output_items[0], out_device_buffer, threadID);
			acc_init_done = 1;
		} else {
            if( noutput_items*d_vlen*sizeof(const FComplex) <= in_device_buffer_size ) {
                accComplexToMag_map(noutput_items*d_vlen, (const FComplex *)input_items[0], in_device_buffer, (float *)output_items[0], out_device_buffer, threadID);
            }
		}

        // Do the work
        accComplexToMag_kernel(noutput_items*d_vlen, (const FComplex *)input_items[0], (float *)output_items[0], threadID);

        if( noutput_items*d_vlen*sizeof(const FComplex) <= in_device_buffer_size ) {
            accComplexToMag_unmap((const FComplex *)input_items[0], (float *)output_items[0], threadID);
        }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    int
    accComplexToMag_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        int retVal = processOpenACC(noutput_items,d_ninput_items,input_items,output_items);

      // Tell runtime system how many output items we produced.
      return retVal;
    }

  } /* namespace openacc */
} /* namespace gr */

