/* -*- c++ -*- */

#define COSMIC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "cosmic_swig_doc.i"

%{
#include "cosmic/cc_blocks_complex_to_mag_squared.h"
%}

%include "cosmic/cc_blocks_complex_to_mag_squared.h"
GR_SWIG_BLOCK_MAGIC2(cosmic, cc_blocks_complex_to_mag_squared);
