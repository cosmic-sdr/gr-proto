/* -*- c++ -*- */

#define OPENACC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "openacc_swig_doc.i"

%{
#include "openacc/accLog.h"
%}

%include "openacc/accLog.h"
GR_SWIG_BLOCK_MAGIC2(openacc, accLog);
