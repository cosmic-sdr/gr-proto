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
#include "accComplexToMagPhase_impl.h"
#include <volk/volk.h>
#include "fast_atan2f.h"

namespace gr {
  namespace openacc {

    accComplexToMagPhase::sptr
    accComplexToMagPhase::make(int contextType, int deviceId, size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new accComplexToMagPhase_impl(contextType, deviceId, vlen));
    }

    /*
     * The private constructor
     */
    accComplexToMagPhase_impl::accComplexToMagPhase_impl(int contextType, int deviceId, size_t vlen)
      : gr::sync_block("accComplexToMagPhase",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen),
              gr::io_signature::make(2, 2, sizeof(float)*vlen)), d_vlen(vlen),
        GRACCBase(contextType, deviceId)
    {
		//if( gracc_counter <= 1 ) {
        	accComplexToMagPhase_init(deviceType, deviceId, threadID);
		//}
		//acc_init_done = 1;
		in_device_buffer_size = 0;
        out_device_buffer_size = 0;
    }

    /*
     * Our virtual destructor.
     */
    accComplexToMagPhase_impl::~accComplexToMagPhase_impl()
    {
    }

    int accComplexToMagPhase_impl::testCPU(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
        {
        const gr_complex *in = (const gr_complex *) input_items[0];
        float *out0 = (float *) output_items[0];
        float* out1 = (float *) output_items[1];
        int noi = noutput_items * d_vlen;

        volk_32fc_magnitude_32f_u(out0, in, noi);

        // The fast_atan2f is faster than Volk
        for (int i = 0; i < noi; i++){
        //    out[i] = std::arg (in[i]);
            out1[i] = gr::openacc::fast_atan2f(in[i].imag(),in[i].real());
        }

        return noutput_items;
    }

    int accComplexToMagPhase_impl::testOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items) {
        return processOpenACC(noutput_items,ninput_items,input_items, output_items);
    }

    int accComplexToMagPhase_impl::processOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
    {
        // Protect context from switching
        gr::thread::scoped_lock guard(d_mutex);
		if( acc_init_done == 0 ) {
        	//accComplexToMagPhase_init(deviceType, deviceId, threadID);
            in_device_buffer_size = noutput_items*d_vlen*sizeof(const FComplex)*3;
            out_device_buffer_size = noutput_items*d_vlen*sizeof(float)*3;
            accComplexToMagPhase_deviceData_malloc(in_device_buffer_size, (d_void **)&in_device_buffer, out_device_buffer_size, (d_void **)&out_device_buffer1, (d_void **)&out_device_buffer2, threadID);
            accComplexToMagPhase_map(noutput_items*d_vlen, (const FComplex *)input_items[0], in_device_buffer, (float *)output_items[0], out_device_buffer1, (float *)output_items[1], out_device_buffer2, threadID);

			acc_init_done = 1;
        } else {
            if( noutput_items*d_vlen*sizeof(const FComplex) <= in_device_buffer_size ) {
            	accComplexToMagPhase_map(noutput_items*d_vlen, (const FComplex *)input_items[0], in_device_buffer, (float *)output_items[0], out_device_buffer1, (float *)output_items[1], out_device_buffer2, threadID);
            }
		}

        // Do the work
        accComplexToMagPhase_kernel(noutput_items*d_vlen, (const FComplex *)input_items[0], (float *)output_items[0], (float *)output_items[1], threadID);

        if( noutput_items*d_vlen*sizeof(const FComplex) <= in_device_buffer_size ) {
            accComplexToMagPhase_unmap((const FComplex *)input_items[0], (float *)output_items[0], (float *)output_items[1], threadID);
        }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    int
    accComplexToMagPhase_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        int retVal = processOpenACC(noutput_items,d_ninput_items,input_items,output_items);

      // Tell runtime system how many output items we produced.
      return retVal;
    }

  } /* namespace openacc */
} /* namespace gr */

