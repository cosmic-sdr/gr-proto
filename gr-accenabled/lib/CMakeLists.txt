# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

set(VOLK_LIBRARIES volk)

set (CMAKE_CXX_STANDARD 11)

IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
	MESSAGE(STATUS "building for debug...")
ELSE(CMAKE_BUILD_TYPE MATCHES DEBUG)
	MESSAGE(STATUS "Release mode: increasing compiler optimizations...")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR} ${OpenCL_INCLUDE_DIRS} ${OpenARC_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
link_directories(${FFTW3F_LIBRARY_DIRS})

############################################
# Generate OpenACC output files by OpenARC #
############################################
add_custom_command(OUTPUT clLog_kernel.cpp openarc_kernel.cl
	COMMAND ${OpenARC_BIN_DIR}/openarc -addIncludePath=${OpenARC_INCLUDE_DIR} -gpuConfFile=${CMAKE_CURRENT_SOURCE_DIR}/openarcConf_clLog.txt ${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.c; cp ${CMAKE_CURRENT_SOURCE_DIR}/cetus_output/clLog_kernel.cpp ${CMAKE_CURRENT_SOURCE_DIR}/; cp ${CMAKE_CURRENT_SOURCE_DIR}/cetus_output/openarc_kernel.cl ${CMAKE_CURRENT_SOURCE_DIR}/; rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/cetus_output
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.c)

list(APPEND clenabled_sources
    clMathConst_impl.cc
    GRCLBase.cpp
    clMathOp_impl.cc
    firdes.cc
    window.cc
    fft_filter.cc
    fft.cc
    clFilter_impl.cc
    clQuadratureDemod_impl.cc
    fast_atan2f.cc
    clFFT_impl.cc
    clLog_impl.cc
    clLog_kernel.cpp
    clSNR_impl.cc
    clComplexToArg_impl.cc
    clComplexToMagPhase_impl.cc
    clMagPhaseToComplex_impl.cc
    clComplexToMag_impl.cc
    clKernel1To1_impl.cc
    clKernel2To1_impl.cc
    clSignalSource_impl.cc
    clCostasLoop_impl.cc
)

set(clenabled_sources "${clenabled_sources}" PARENT_SCOPE)
if(NOT clenabled_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT clenabled_sources)

add_library(gnuradio-accenabled SHARED ${clenabled_sources})
target_link_libraries(gnuradio-accenabled ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES} ${OpenCL_LIBRARY} gnuradio-blocks gnuradio-filter ${VOLK_LIBRARIES} ${Boost_LIBRARIES} ${FFTW3F_LIBRARIES} ${CLFFT_LIBRARIES} ${OpenARC_LIBRARIES})
set_target_properties(gnuradio-accenabled PROPERTIES DEFINE_SYMBOL "gnuradio_clenabled_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-accenabled PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-accenabled RUNTIME_COMPONENT "clenabled_runtime" DEVEL_COMPONENT "clenabled_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_clenabled_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_clenabled.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clenabled.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clCostasLoop.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clSignalSource.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clKernel2To1.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clKernel1To1.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clComplexToMag.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clMagPhaseToComplex.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clComplexToMagPhase.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clComplexToArg.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clSNR.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clLog.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clFFT.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clQuadratureDemod.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clFilter.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clMathOp.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_clMathConst.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clMathOp_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clMathConst_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/GRCLBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clFilter_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clQuadratureDemod_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/fast_atan2f.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clFFT_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clLog_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clSNR_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMag_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMagPhase_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clMagPhaseToComplex_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clSignalSource_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clCostasLoop_impl.cc
)

add_executable(test-accenabled ${test_clenabled_sources})

target_link_libraries(
  test-accenabled
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  ${VOLK_LIBRARIES}
  ${FFTW3F_LIBRARIES}
  ${OpenCL_LIBRARY}
  gnuradio-accenabled
  ${CLFFT_LIBRARIES}
  gnuradio-blocks
  gnuradio-filter
)

GR_ADD_TEST(test_clenabled test-accenabled)

install(TARGETS test-accenabled DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)

########################################################################
# Build and register clview
########################################################################
add_executable(clview clview.cc)

target_link_libraries(
  clview
  OpenCL
)

install(TARGETS clview DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)

########################################################################
# Build and register test-acckernel
########################################################################
list(APPEND test_clkernel_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test-clkernel.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/GRCLBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clKernel1To1_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clKernel2To1_impl.cc
)

add_executable(test-acckernel ${test_clkernel_sources})


target_link_libraries(
  test-acckernel
  ${OpenCL_LIBRARY}
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  gnuradio-accenabled
)

install(TARGETS test-acckernel DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)

########################################################################
# Build and register test-accfilter
########################################################################
list(APPEND test_clfilter_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test-clfilter.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clFilter_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/GRCLBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cc
)

add_executable(test-accfilter ${test_clfilter_sources})

target_link_libraries(
  test-accfilter
  ${OpenCL_LIBRARY}
  ${GNURADIO_RUNTIME_LIBRARIES}
  gnuradio-filter
  ${Boost_LIBRARIES}
  gnuradio-accenabled
)

install(TARGETS test-accfilter DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)

########################################################################
# Build and register test-accenabled-fft
########################################################################
list(APPEND test_clsingle_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test-clenabled-fft.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clFFT_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/GRCLBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cc
)

add_executable(test-accenabled-fft ${test_clsingle_sources})


target_link_libraries(
  test-accenabled-fft
  ${OpenCL_LIBRARY}
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  gnuradio-accenabled
)

########################################################################
# Build and register test-acclog
########################################################################
list(APPEND test_cllog_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test-cllog.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clLog_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.cpp
)

add_executable(test-acclog ${test_cllog_sources})


target_link_libraries(
  test-acclog
  ${OpenCL_LIBRARY}
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  gnuradio-accenabled
)

install(TARGETS test-acclog DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)
install(FILES openarc_kernel.cl DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 
########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

