/* -*- c++ -*- */

#define ORNL_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ornl_swig_doc.i"

%{
#include "ornl/vecadd.h"
#include "ornl/saxpy.h"
%}

%include "ornl/vecadd.h"
GR_SWIG_BLOCK_MAGIC2(ornl, vecadd);
%include "ornl/saxpy.h"
GR_SWIG_BLOCK_MAGIC2(ornl, saxpy);
