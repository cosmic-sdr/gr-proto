/* -*- c++ -*- */

#define OPENACC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "openacc_swig_doc.i"

%{
#include "openacc/accLog.h"
#include "openacc/accComplexToArg.h"
#include "openacc/accComplexToMag.h"
#include "openacc/accComplexToMagPhase.h"
#include "openacc/accMagPhaseToComplex.h"
%}

%include "openacc/accLog.h"
GR_SWIG_BLOCK_MAGIC2(openacc, accLog);
%include "openacc/accComplexToArg.h"
GR_SWIG_BLOCK_MAGIC2(openacc, accComplexToArg);
%include "openacc/accComplexToMag.h"
GR_SWIG_BLOCK_MAGIC2(openacc, accComplexToMag);
%include "openacc/accComplexToMagPhase.h"
GR_SWIG_BLOCK_MAGIC2(openacc, accComplexToMagPhase);
%include "openacc/accMagPhaseToComplex.h"
GR_SWIG_BLOCK_MAGIC2(openacc, accMagPhaseToComplex);
