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


#ifndef INCLUDED_COSMIC_CC_BLOCKS_COMPLEX_TO_MAG_SQUARED_H
#define INCLUDED_COSMIC_CC_BLOCKS_COMPLEX_TO_MAG_SQUARED_H

#include <cosmic/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace cosmic {

    /*!
     * \brief <+description of block+>
     * \ingroup cosmic
     *
     */
    class COSMIC_API cc_blocks_complex_to_mag_squared : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<cc_blocks_complex_to_mag_squared> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of cosmic::cc_blocks_complex_to_mag_squared.
       *
       * To avoid accidental use of raw pointers, cosmic::cc_blocks_complex_to_mag_squared's
       * constructor is in a private implementation
       * class. cosmic::cc_blocks_complex_to_mag_squared::make is the public interface for
       * creating new instances.
       */
      static sptr make(size_t vlen=1);
    };

  } // namespace cosmic
} // namespace gr

#endif /* INCLUDED_COSMIC_CC_BLOCKS_COMPLEX_TO_MAG_SQUARED_H */

