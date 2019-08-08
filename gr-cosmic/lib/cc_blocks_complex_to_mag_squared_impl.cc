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
#include "cc_blocks_complex_to_mag_squared_impl.h"
#include <volk/volk.h>

namespace gr {
  namespace cosmic {

    cc_blocks_complex_to_mag_squared::sptr
    cc_blocks_complex_to_mag_squared::make(size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new cc_blocks_complex_to_mag_squared_impl(vlen));
    }

    /*
     * The private constructor
     */
    cc_blocks_complex_to_mag_squared_impl::cc_blocks_complex_to_mag_squared_impl(size_t vlen)
      : gr::sync_block("cc_blocks_complex_to_mag_squared",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen),
              gr::io_signature::make(1, 1, sizeof(float)*vlen)), d_vlen(vlen)
    {
      const int alignment_multiple =
      volk_get_alignment() / sizeof(float);
      set_alignment(std::max(1,alignment_multiple));
    }

    /*
     * Our virtual destructor.
     */
    cc_blocks_complex_to_mag_squared_impl::~cc_blocks_complex_to_mag_squared_impl()
    {
    }

    int
    cc_blocks_complex_to_mag_squared_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];
      int noi = noutput_items * d_vlen;

      volk_32fc_magnitude_squared_32f(out, in, noi);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace cosmic */
} /* namespace gr */

