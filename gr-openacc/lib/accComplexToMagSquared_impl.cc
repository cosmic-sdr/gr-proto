/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
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
#include "accComplexToMagSquared_impl.h"
#include <volk/volk.h>

namespace gr {
  namespace openacc {

    accComplexToMagSquared::sptr
    accComplexToMagSquared::make(int contextType, int deviceId, size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new accComplexToMagSquared_impl(contextType, deviceId, vlen));
    }

    /*
     * The private constructor
     */
    accComplexToMagSquared_impl::accComplexToMagSquared_impl(int contextType, int deviceId, size_t vlen)
      : gr::sync_block("accComplexToMagSquared",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen),
              gr::io_signature::make(1, 1, sizeof(float)*vlen)), d_vlen(vlen),
        GRACCBase(contextType, deviceId)
    {
        const int alignment_multiple =
        volk_get_alignment() / sizeof(float);
        set_alignment(std::max(1,alignment_multiple));
		//if( gracc_counter <= 1 ) {
        	accComplexToMagSquared_init(deviceType, deviceId, threadID);
		//}
		acc_init_done = 1;
    }

    /*
     * Our virtual destructor.
     */
    accComplexToMagSquared_impl::~accComplexToMagSquared_impl()
    {
    }

    int accComplexToMagSquared_impl::testCPU(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
        {   
        const gr_complex *in = (const gr_complex*)input_items[0];
        float *out = (float*)output_items[0];
        int noi = noutput_items * d_vlen;
/*
 *         for(int i = 0; i < noi; i++) {
 *                     out[i] = in[i].imag()*in[i].imag()+in[i].real()*in[i].real();
 *                             }
 *                             */
        volk_32fc_magnitude_squared_32f(out, in, noi);

        return noutput_items;
    }

    int accComplexToMagSquared_impl::testOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items) {
        return processOpenACC(noutput_items,ninput_items,input_items, output_items);
    }

    int accComplexToMagSquared_impl::processOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
    {
        // Protect context from switching
        gr::thread::scoped_lock guard(d_mutex);
		if( acc_init_done == 0 ) {
        	accComplexToMagSquared_init(deviceType, deviceId, threadID);
			acc_init_done = 1;
		}

        // Do the work
        accComplexToMagSquared_kernel(noutput_items*d_vlen, (const FComplex *)input_items[0], (float *)output_items[0], threadID);

      // Tell runtime system how many output items we produced.
      return noutput_items;
	}

    int
    accComplexToMagSquared_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
        int retVal = processOpenACC(noutput_items,d_ninput_items,input_items,output_items);

      // Tell runtime system how many output items we produced.
      return retVal;
    }

  } /* namespace openacc */
} /* namespace gr */

