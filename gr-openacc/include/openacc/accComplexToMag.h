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


#ifndef INCLUDED_OPENACC_ACCCOMPLEXTOMAG_H
#define INCLUDED_OPENACC_ACCCOMPLEXTOMAG_H

#include <openacc/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace openacc {

    /*!
     * \brief <+description of block+>
     * \ingroup openacc
     *
     */
    class OPENACC_API accComplexToMag : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<accComplexToMag> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of openacc::accComplexToMag.
       *
       * To avoid accidental use of raw pointers, openacc::accComplexToMag's
       * constructor is in a private implementation
       * class. openacc::accComplexToMag::make is the public interface for
       * creating new instances.
       */
      static sptr make(int contextType, int deviceId);
    };

  } // namespace openacc
} // namespace gr

#endif /* INCLUDED_OPENACC_ACCCOMPLEXTOMAG_H */
