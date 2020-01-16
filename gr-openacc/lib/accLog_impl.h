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

#ifndef INCLUDED_OPENACC_ACCLOG_IMPL_H
#define INCLUDED_OPENACC_ACCLOG_IMPL_H

#include <openacc/accLog.h>
#include "GRACCBase.h"
#include "accLog_kernel.h"

namespace gr {
  namespace openacc {

    class accLog_impl : public accLog, public GRACCBase
    {
     private:
      // Nothing to declare in this block.
      float n_val;
      float k_val;
      gr_vector_int d_ninput_items;
      size_t d_vlen;
      int gracc_copy_in;
      int gracc_copy_out;

     public:
      accLog_impl(int contextType, int deviceId, float nValue, float kValue, size_t vlen, int copy_in, int copy_out);
      ~accLog_impl();

      int testCPU(int noutput_items,
              gr_vector_int &ninput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items);

      int processOpenACC(int noutput_items,
              gr_vector_int &ninput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items);

      int testOpenACC(int noutput_items,
              gr_vector_int &ninput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items);
      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace openacc
} // namespace gr

#endif /* INCLUDED_OPENACC_ACCLOG_IMPL_H */

