/* -*- c++ -*- */
/* 
 * Copyright 2017 ghostop14.
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
#include "clMagPhaseToComplex_impl.h"

namespace gr {
  namespace clenabled {

    clMagPhaseToComplex::sptr
    clMagPhaseToComplex::make(int openCLPlatformType,int devSelector,int platformId, int devId,int setDebug)
    {
    	if (setDebug == 1)
		  return gnuradio::get_initial_sptr
			(new clMagPhaseToComplex_impl(openCLPlatformType,devSelector,platformId,devId,true));
    	else
  		  return gnuradio::get_initial_sptr
  			(new clMagPhaseToComplex_impl(openCLPlatformType,devSelector,platformId,devId,false));
    }

    /*
     * The private constructor
     */
    clMagPhaseToComplex_impl::clMagPhaseToComplex_impl(int openCLPlatformType,int devSelector,int platformId, int devId,bool setDebug)
      : gr::sync_block("clMagPhaseToComplex",
              gr::io_signature::make(2, 2, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
  	  	  	  GRACCBase(openCLPlatformType,devSelector,platformId,devId,setDebug)
    {
		clMagPhaseToComplex_init(deviceType, devSelector, devId);
    	int imaxItems=gr::block::max_noutput_items();
    	if (imaxItems==0)
    		imaxItems=8192;
/*
    	if (imaxItems > maxConstItems) {
    		imaxItems = maxConstItems;
    	}

		try {
			// optimize for constant memory space
			gr::block::set_max_noutput_items(imaxItems);
		}
		catch(...) {

		}
*/
        setBufferLength(imaxItems);

        // And finally optimize the data we get based on the preferred workgroup size.
        // Note: We can't do this until the kernel is compiled and since it's in the block class
        // it has to be done here.
        // Note: for CPU's adjusting the workgroup size away from 1 seems to decrease performance.
        // For GPU's setting it to the preferred size seems to have the best performance.
		try {
			if (contextType != OCLTYPE_CPU) {
				gr::block::set_output_multiple(preferredWorkGroupSizeMultiple);
			}
			else {
				// Keep the IO somewhat aligned
				gr::block::set_output_multiple(32);
			}
		}
        catch (...) {

        }
}

    /*
     * Our virtual destructor.
     */
    clMagPhaseToComplex_impl::~clMagPhaseToComplex_impl()
    {
    	if (curBufferSize > 0)
    		stop();
    }

    bool clMagPhaseToComplex_impl::stop() {
    	curBufferSize = 0;

    	return GRACCBase::stop();
    }

    void clMagPhaseToComplex_impl::setBufferLength(int numItems) {
        curBufferSize=numItems;
    }

    /*
     * Our virtual destructor.
     */
    int clMagPhaseToComplex_impl::testCPU(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
    	{
        float        *mag = (float *)input_items[0];
        float        *phase = (float *)input_items[1];
        gr_complex *out = (gr_complex *) output_items[0];

        int d_vlen = 1;

        for (size_t j = 0; j < noutput_items*d_vlen; j++)
          out[j] = gr_complex (mag[j]*cos(phase[j]),mag[j]*sin(phase[j]));

        return noutput_items;
    }

    int clMagPhaseToComplex_impl::testOpenCL(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items) {
    	return processOpenCL(noutput_items,ninput_items,input_items, output_items);
    }

    int clMagPhaseToComplex_impl::processOpenCL(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
    {
    	if (noutput_items > curBufferSize) {
    		setBufferLength(noutput_items);
    	}

    	// Protect context from switching
        gr::thread::scoped_lock guard(d_mutex);

		// Do the work

		unsigned int localWGSize=0;

		if (contextType!=OCLTYPE_CPU) {
			if (noutput_items % preferredWorkGroupSizeMultiple == 0) {
				// for some reason problems start to happen when we're no longer using constant memory
				localWGSize=preferredWorkGroupSizeMultiple;
			}
		}

		clMagPhaseToComplex_kernel(noutput_items, (const float *)input_items[0], (const float *)input_items[1], (FComplex *)output_items[0]);
		// Do the work

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }


    int
    clMagPhaseToComplex_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
    	if (debugMode && CLPRINT_NITEMS)
    		std::cout << "clMagPhaseToComplex noutput_items: " << noutput_items << std::endl;

        int retVal = processOpenCL(noutput_items,d_ninput_items,input_items,output_items);

      // Tell runtime system how many output items we produced.
      return retVal;
    }

  } /* namespace clenabled */
} /* namespace gr */

