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
#include "clLog_impl.h"
#include "clLog_kernel.h"

namespace gr {
  namespace clenabled {

    clLog::sptr
    clLog::make(int openCLPlatformType,int devSelector,int platformId, int devId,float nValue,float kValue,int setDebug)
    {

      	if (setDebug == 1) {
            return gnuradio::get_initial_sptr
              (new clLog_impl(openCLPlatformType,devSelector,platformId,devId,nValue,kValue,true));
      	}
      	else {
            return gnuradio::get_initial_sptr
              (new clLog_impl(openCLPlatformType,devSelector,platformId,devId,nValue,kValue,false));
      	}
    }

    /*
     * The private constructor
     */
    clLog_impl::clLog_impl(int openCLPlatformType,int devSelector,int platformId, int devId,float nValue,float kValue,bool setDebug)
      : gr::sync_block("clLog",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))

    {
    	n_val = nValue;
    	k_val = kValue;

    	int imaxItems=gr::block::max_noutput_items();
    	if (imaxItems==0)
    		imaxItems=8192;

        setBufferLength(imaxItems);
		acc_initializer(openCLPlatformType, devSelector, platformId, devId);

        // And finally optimize the data we get based on the preferred workgroup size.
        // Note: We can't do this until the kernel is compiled and since it's in the block class
        // it has to be done here.
        // Note: for CPU's adjusting the workgroup size away from 1 seems to decrease performance.
        // For GPU's setting it to the preferred size seems to have the best performance.
		try {
			if (openCLPlatformType != OCLTYPE_CPU) {
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

    void clLog_impl::setBufferLength(int numItems) {
        curBufferSize=numItems;
    }

    /*
     * Our virtual destructor.
     */
    clLog_impl::~clLog_impl()
    {
    	if (curBufferSize > 0)
    		stop();
    }

    bool clLog_impl::stop() {
    	curBufferSize = 0;

    	return true;
    }

    int clLog_impl::testCPU(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items)
    	{

        const float *in1 = (const float *) input_items[0];
        float *out = (float *) output_items[0];

		for (int i=0;i<noutput_items;i++) {
			out[i] = n_val * log10(in1[i]) + k_val;
		}

    	return noutput_items;
    }

    int clLog_impl::testOpenCL(int noutput_items,
            gr_vector_int &ninput_items,
            gr_vector_const_void_star &input_items,
            gr_vector_void_star &output_items) {
    	return processOpenCL(noutput_items,ninput_items,input_items, output_items);
    }

    int clLog_impl::processOpenCL(int noutput_items,
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

		if (contextType!=CL_DEVICE_TYPE_CPU) {
			if (noutput_items % preferredWorkGroupSizeMultiple == 0) {
				// for some reason problems start to happen when we're no longer using constant memory
				localWGSize=preferredWorkGroupSizeMultiple;
			}
		}

		// Do the work
        log_kernel(noutput_items, n_val, k_val, localWGSize, (const float *)input_items[0], (float *)output_items[0]);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }


    int
    clLog_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
    	if (debugMode && CLPRINT_NITEMS)
    		std::cout << "clLog noutput_items: " << noutput_items << std::endl;

        int retVal = processOpenCL(noutput_items,d_ninput_items,input_items,output_items);

        // Tell runtime system how many output items we produced.
        return retVal;
    }

  } /* namespace clenabled */
} /* namespace gr */

