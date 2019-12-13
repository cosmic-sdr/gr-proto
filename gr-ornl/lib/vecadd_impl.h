/* -*- c++ -*- */
/* 
 * Copyright 2019 ornl.
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

#ifndef INCLUDED_ORNL_VECADD_IMPL_H
#define INCLUDED_ORNL_VECADD_IMPL_H

#include <ornl/vecadd.h>
#include <brisbane/brisbane.h>

namespace gr {
  namespace ornl {

    class vecadd_impl : public vecadd
    {
     private:
      // Nothing to declare in this block.
      int device_;
      int connected_;
      bool mapped_;
      brisbane_kernel kernel_vecadd;

     public:
      vecadd_impl(int device, int connected);
      ~vecadd_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ornl
} // namespace gr

#endif /* INCLUDED_ORNL_VECADD_IMPL_H */

