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
    accComplexToMagPhase::make(int contextType, int deviceId, size_t vlen, int copy_in, int copy_out)
    {
      return gnuradio::get_initial_sptr
        (new accComplexToMagPhase_impl(contextType, deviceId, vlen, copy_in, copy_out));
    }

    /*
     * The private constructor
     */
    accComplexToMagPhase_impl::accComplexToMagPhase_impl(int contextType, int deviceId, size_t vlen, int copy_in, int copy_out)
      : gr::sync_block("accComplexToMagPhase",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen),
              gr::io_signature::make(2, 2, sizeof(float)*vlen)), d_vlen(vlen), gracc_copy_in(copy_in), gracc_copy_out(copy_out),
        GRACCBase(contextType, deviceId)
    {
		//if( gracc_counter <= 1 ) {
        	accComplexToMagPhase_init(deviceType, deviceId, threadID);
		//}
		//acc_init_done = 1;
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
        int max_noutputs = max_noutput_items();
        if( acc_init_done == 0 ) {
        	//accComplexToMagPhase_init(deviceType, deviceId, threadID);
            if( max_noutputs == 0 ) {
                printf("[ERROR in accComplexToMagPhase] max_noutput_items() is NOT set properly; exit!\n");
                exit(EXIT_FAILURE);
            }
            gracc_pcopyin((h_void*)input_items[0], max_noutputs*sizeof(const FComplex), threadID);
            gracc_pcreate((h_void*)output_items[0], max_noutputs*sizeof(float),  threadID);
            gracc_pcreate((h_void*)output_items[1], max_noutputs*sizeof(float),  threadID);
            acc_init_done = 1;
        } else if( gracc_copy_in == 1 ) {
            gracc_update_device((h_void*)input_items[0], noutput_items*sizeof(const FComplex),  threadID);
        }

        // Do the work
        accComplexToMagPhase_kernel(noutput_items*d_vlen, (const FComplex *)input_items[0], (float *)output_items[0], (float *)output_items[1], threadID);

        if( gracc_copy_out == 1 ) {
            gracc_update_self((h_void*)output_items[0], noutput_items*sizeof(float),  threadID);
            gracc_update_self((h_void*)output_items[1], noutput_items*sizeof(float),  threadID);
        }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    int
    accComplexToMagPhase_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
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

