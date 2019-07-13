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
    accComplexToMag::make(int contextType, int deviceId)
    {
      return gnuradio::get_initial_sptr
        (new accComplexToMag_impl(contextType, deviceId));
    }

    /*
     * The private constructor
     */
    accComplexToMag_impl::accComplexToMag_impl(int contextType, int deviceId)
      : gr::sync_block("accComplexToMag",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float))),
        GRACCBase(contextType, deviceId)
    {
        accComplexToMag_init(deviceType, deviceId);
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
        gr_complex *in = (gr_complex*)input_items[0];
        float *out = (float*)output_items[0];
/*
 *         for(int i = 0; i < noutput_items; i++) {
 *                     out[i] = sqrt(in[i].imag()*in[i].imag()+in[i].real()*in[i].real());
 *                             }
 *                             */
        volk_32fc_magnitude_32f_u(out, in, noutput_items);

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

        // Do the work
        accComplexToMag_kernel(noutput_items, (const FComplex *)input_items[0], (float *)output_items[0]);

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
