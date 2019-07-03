/* -*- c++ -*- */
/* 
 * Copyright 2019 Oak Ridge National Laboratory.
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

#ifndef INCLUDED_COSMIC_CC_BLOCKS_COMPLEX_TO_MAG_SQUARED_IMPL_H
#define INCLUDED_COSMIC_CC_BLOCKS_COMPLEX_TO_MAG_SQUARED_IMPL_H

#include <cosmic/cc_blocks_complex_to_mag_squared.h>

namespace gr {
  namespace cosmic {

    class cc_blocks_complex_to_mag_squared_impl : public cc_blocks_complex_to_mag_squared
    {
     private:
	size_t d_vlen;	
     public:
      cc_blocks_complex_to_mag_squared_impl(size_t vlen);
      ~cc_blocks_complex_to_mag_squared_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace cosmic
} // namespace gr

#endif /* INCLUDED_COSMIC_CC_BLOCKS_COMPLEX_TO_MAG_SQUARED_IMPL_H */

