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
#include "accMagPhaseToComplex_impl.h"

namespace gr {
  namespace openacc {

    accMagPhaseToComplex::sptr
    accMagPhaseToComplex::make(int contextType, int deviceId, size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new accMagPhaseToComplex_impl(contextType, deviceId, vlen));
    }

    /*
     * The private constructor
     */
    accMagPhaseToComplex_impl::accMagPhaseToComplex_impl(int contextType, int deviceId, size_t vlen)
      : gr::sync_block("accMagPhaseToComplex",
              gr::io_signature::make(2, 2, sizeof(float)*vlen),
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen)), d_vlen(vlen),
        GRACCBase(contextType, deviceId)
    {
		//if( gracc_counter <= 1 ) {
        	accMagPhaseToComplex_init(deviceType, deviceId);
		//}
		acc_init_done = 1;
    }

    /*
     * Our virtual destructor.
     */
    accMagPhaseToComplex_impl::~accMagPhaseToComplex_impl()
    {
    }

    int accMagPhaseToComplex_impl::testCPU(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
        {   
        float        *mag = (float *)input_items[0];
        float        *phase = (float *)input_items[1];
        gr_complex *out = (gr_complex *) output_items[0];
        int noi = noutput_items * d_vlen;

        for (size_t j = 0; j < noi; j++)
          out[j] = gr_complex (mag[j]*cos(phase[j]),mag[j]*sin(phase[j]));

        return noutput_items;
    }   

    int accMagPhaseToComplex_impl::testOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items) {
        return processOpenACC(noutput_items,ninput_items,input_items, output_items);
    }

    int accMagPhaseToComplex_impl::processOpenACC(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
    {
        // Protect context from switching
        gr::thread::scoped_lock guard(d_mutex);
		if( acc_init_done == 0 ) {
        	accMagPhaseToComplex_init(deviceType, deviceId);
			acc_init_done = 1;
		}

        accMagPhaseToComplex_kernel(noutput_items*d_vlen, (const float *)input_items[0], (const float *)input_items[1], (FComplex *)output_items[0]);
        // Do the work

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    int
    accMagPhaseToComplex_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        int retVal = processOpenACC(noutput_items,d_ninput_items,input_items,output_items);

      // Tell runtime system how many output items we produced.
      return retVal;
    }

  } /* namespace openacc */
} /* namespace gr */

