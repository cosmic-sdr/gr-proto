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
#add_custom_command(OUTPUT clLog_kernel.cpp openarc_kernel_clLog.cl clComplexToArg_kernel.cpp openarc_kernel_clComplexToArg.cl
#	COMMAND ${OpenARC_BIN_DIR}/openarc -addIncludePath=${OpenARC_INCLUDE_DIR} -gpuConfFile=${CMAKE_CURRENT_SOURCE_DIR}/openarcConf_clLog.txt ${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clLog/clLog_kernel.cpp ${CMAKE_CURRENT_BINARY_DIR}/ && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clLog/openarc_kernel_clLog.cl ${CMAKE_CURRENT_BINARY_DIR}/ && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clLog
#	COMMAND ${OpenARC_BIN_DIR}/openarc -addIncludePath=${OpenARC_INCLUDE_DIR} -gpuConfFile=${CMAKE_CURRENT_SOURCE_DIR}/openarcConf_clComplexToArg.txt ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToArg/clComplexToArg_kernel.cpp ${CMAKE_CURRENT_BINARY_DIR}/ && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToArg/openarc_kernel_clComplexToArg.cl ${CMAKE_CURRENT_BINARY_DIR}/ && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToArg
#	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.c ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_kernel.c)

add_custom_command(OUTPUT clLog_kernel.cpp openarc_kernel_clLog.cl
	COMMAND ${OpenARC_BIN_DIR}/openarc -addIncludePath=${OpenARC_INCLUDE_DIR} -gpuConfFile=${CMAKE_CURRENT_SOURCE_DIR}/openarcConf_clLog.txt ${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clLog/clLog_kernel.cpp ${CMAKE_CURRENT_BINARY_DIR}/ && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clLog/openarc_kernel_clLog.cl ${CMAKE_CURRENT_BINARY_DIR}/ && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clLog
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.c)

add_custom_command(OUTPUT clComplexToArg_kernel.cpp openarc_kernel_clComplexToArg.cl
	COMMAND ${OpenARC_BIN_DIR}/openarc -addIncludePath=${OpenARC_INCLUDE_DIR} -gpuConfFile=${CMAKE_CURRENT_SOURCE_DIR}/openarcConf_clComplexToArg.txt ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToArg/clComplexToArg_kernel.cpp ${CMAKE_CURRENT_BINARY_DIR}/ && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToArg/openarc_kernel_clComplexToArg.cl ${CMAKE_CURRENT_BINARY_DIR}/ && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToArg
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_kernel.c)

add_custom_command(OUTPUT clComplexToMag_kernel.cpp openarc_kernel_clComplexToMag.cl
	COMMAND ${OpenARC_BIN_DIR}/openarc -addIncludePath=${OpenARC_INCLUDE_DIR} -gpuConfFile=${CMAKE_CURRENT_SOURCE_DIR}/openarcConf_clComplexToMag.txt ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMag_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToMag/clComplexToMag_kernel.cpp ${CMAKE_CURRENT_BINARY_DIR}/ && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToMag/openarc_kernel_clComplexToMag.cl ${CMAKE_CURRENT_BINARY_DIR}/ && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToMag
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMag_kernel.c)

add_custom_command(OUTPUT clComplexToMagPhase_kernel.cpp openarc_kernel_clComplexToMagPhase.cl
	COMMAND ${OpenARC_BIN_DIR}/openarc -addIncludePath=${OpenARC_INCLUDE_DIR} -gpuConfFile=${CMAKE_CURRENT_SOURCE_DIR}/openarcConf_clComplexToMagPhase.txt ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMagPhase_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToMagPhase/clComplexToMagPhase_kernel.cpp ${CMAKE_CURRENT_BINARY_DIR}/ && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToMagPhase/openarc_kernel_clComplexToMagPhase.cl ${CMAKE_CURRENT_BINARY_DIR}/ && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clComplexToMagPhase
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMagPhase_kernel.c)

add_custom_command(OUTPUT clMagPhaseToComplex_kernel.cpp openarc_kernel_clMagPhaseToComplex.cl
	COMMAND ${OpenARC_BIN_DIR}/openarc -addIncludePath=${OpenARC_INCLUDE_DIR} -gpuConfFile=${CMAKE_CURRENT_SOURCE_DIR}/openarcConf_clMagPhaseToComplex.txt ${CMAKE_CURRENT_SOURCE_DIR}/clMagPhaseToComplex_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clMagPhaseToComplex/clMagPhaseToComplex_kernel.cpp ${CMAKE_CURRENT_BINARY_DIR}/ && cp ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clMagPhaseToComplex/openarc_kernel_clMagPhaseToComplex.cl ${CMAKE_CURRENT_BINARY_DIR}/ && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/cetus_output_clMagPhaseToComplex
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clMagPhaseToComplex_kernel.c)

list(APPEND clenabled_sources
    clMathConst_impl.cc
    GRCLBase.cpp
    GRACCBase.cpp
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
    #acc_helper_clLog.cpp
    clLog_kernel.cpp
    clSNR_impl.cc
    clComplexToArg_impl.cc
    #acc_helper_clComplexToArg.cpp
    clComplexToArg_kernel.cpp
    clComplexToMagPhase_impl.cc
    clComplexToMagPhase_kernel.cpp
    clMagPhaseToComplex_impl.cc
    clMagPhaseToComplex_kernel.cpp
    clComplexToMag_impl.cc
    clComplexToMag_kernel.cpp
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
    ${CMAKE_CURRENT_SOURCE_DIR}/GRACCBase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clFilter_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clQuadratureDemod_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/fast_atan2f.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clFFT_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clLog_impl.cc
    #${CMAKE_CURRENT_BINARY_DIR}/acc_helper_clLog.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/clLog_kernel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clSNR_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMag_impl.cc
    ${CMAKE_CURRENT_BINARY_DIR}/clComplexToMag_kernel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_impl.cc
    #${CMAKE_CURRENT_BINARY_DIR}/acc_helper_clComplexToArg.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/clComplexToArg_kernel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMagPhase_impl.cc
    ${CMAKE_CURRENT_BINARY_DIR}/clComplexToMagPhase_kernel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clMagPhaseToComplex_impl.cc
    ${CMAKE_CURRENT_BINARY_DIR}/clMagPhaseToComplex_kernel.cpp
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
    ${CMAKE_CURRENT_SOURCE_DIR}/GRACCBase.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/clLog_kernel.cpp
    #${CMAKE_CURRENT_BINARY_DIR}/acc_helper_clLog.cpp
)

add_executable(test-acclog ${test_cllog_sources})

target_compile_definitions(
	test-acclog
	PRIVATE -DGRACC_ONLY
)


target_link_libraries(
  test-acclog
  ${OpenCL_LIBRARY}
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  gnuradio-accenabled
)

install(TARGETS test-acclog DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/openarc_kernel_clLog.cl DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

########################################################
# Generate ASPNE model for acclog module using OpenARC #
########################################################
add_custom_target(clLogAspenGen ALL
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/clLog_aspengen.bash -f=${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clLog/clLog.aspen ${CMAKE_CURRENT_SOURCE_DIR} && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clLog
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clLog_aspengen.bash ${CMAKE_CURRENT_SOURCE_DIR}/clLog_kernel.c ${CMAKE_CURRENT_BINARY_DIR}/clComplexToArg_kernel.cpp)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/clLog.aspen DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

########################################################################
# Build and register test-accComplexToArg
########################################################################
list(APPEND test_clcomplextoarg_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test-clcomplextoarg.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/fast_atan2f.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/GRACCBase.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/clComplexToArg_kernel.cpp
    #${CMAKE_CURRENT_BINARY_DIR}/acc_helper_clComplexToArg.cpp
)

add_executable(test-acccomplextoarg ${test_clcomplextoarg_sources})

target_compile_definitions(
	test-acccomplextoarg
	PRIVATE -DGRACC_ONLY
)

target_link_libraries(
  test-acccomplextoarg
  ${OpenCL_LIBRARY}
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  gnuradio-accenabled
)

install(TARGETS test-acccomplextoarg DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/openarc_kernel_clComplexToArg.cl DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

#################################################################
# Generate ASPEN model for acccomplextoarg module using OpenARC #
#################################################################
add_custom_target(clComplexToArgAspenGen ALL
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_aspengen.bash -f=${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clComplexToArg/clComplexToArg.aspen ${CMAKE_CURRENT_SOURCE_DIR} && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clComplexToArg
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_aspengen.bash ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToArg_kernel.c)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/clComplexToArg.aspen DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

add_dependencies(clComplexToArgAspenGen clLogAspenGen)

########################################################################
# Build and register test-accComplexToMag
########################################################################
list(APPEND test_clcomplextomag_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test-clcomplextomag.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMag_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/GRACCBase.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/clComplexToMag_kernel.cpp
)

add_executable(test-acccomplextomag ${test_clcomplextomag_sources})

target_compile_definitions(
	test-acccomplextomag
	PRIVATE -DGRACC_ONLY
)

target_link_libraries(
  test-acccomplextomag
  ${OpenCL_LIBRARY}
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  gnuradio-accenabled
)

install(TARGETS test-acccomplextomag DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/openarc_kernel_clComplexToMag.cl DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

#################################################################
# Generate ASPEN model for acccomplextomag module using OpenARC #
#################################################################
add_custom_target(clComplexToMagAspenGen ALL
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMag_aspengen.bash -f=${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMag_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clComplexToMag/clComplexToMag.aspen ${CMAKE_CURRENT_SOURCE_DIR} && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clComplexToMag
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMag_aspengen.bash ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMag_kernel.c)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/clComplexToMag.aspen DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

add_dependencies(clComplexToMagAspenGen clComplexToArgAspenGen)

########################################################################
# Build and register test-accComplexToMagPhase
########################################################################
list(APPEND test_clcomplextomagphase_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test-clcomplextomagphase.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMagPhase_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/fast_atan2f.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/GRACCBase.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/clComplexToMagPhase_kernel.cpp
)

add_executable(test-acccomplextomagphase ${test_clcomplextomagphase_sources})

target_compile_definitions(
	test-acccomplextomagphase
	PRIVATE -DGRACC_ONLY
)

target_link_libraries(
  test-acccomplextomagphase
  ${OpenCL_LIBRARY}
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  gnuradio-accenabled
)

install(TARGETS test-acccomplextomagphase DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/openarc_kernel_clComplexToMagPhase.cl DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

#################################################################
# Generate ASPEN model for acccomplextomagphase module using OpenARC #
#################################################################
add_custom_target(clComplexToMagPhaseAspenGen ALL
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMagPhase_aspengen.bash -f=${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMagPhase_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clComplexToMagPhase/clComplexToMagPhase.aspen ${CMAKE_CURRENT_SOURCE_DIR} && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clComplexToMagPhase
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMagPhase_aspengen.bash ${CMAKE_CURRENT_SOURCE_DIR}/clComplexToMagPhase_kernel.c)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/clComplexToMagPhase.aspen DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

add_dependencies(clComplexToMagPhaseAspenGen clComplexToMagAspenGen)

########################################################################
# Build and register test-accMagPhaseToComplex
########################################################################
list(APPEND test_clmagphasetocomplex_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test-clmagphasetocomplex.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/clMagPhaseToComplex_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/GRACCBase.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/clMagPhaseToComplex_kernel.cpp
)

add_executable(test-accmagphasetocomplex ${test_clmagphasetocomplex_sources})

target_compile_definitions(
	test-accmagphasetocomplex
	PRIVATE -DGRACC_ONLY
)

target_link_libraries(
  test-accmagphasetocomplex
  ${OpenCL_LIBRARY}
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  gnuradio-accenabled
)

install(TARGETS test-accmagphasetocomplex DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" RUNTIME)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/openarc_kernel_clMagPhaseToComplex.cl DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

#################################################################
# Generate ASPEN model for accmagphasetocomplex module using OpenARC #
#################################################################
add_custom_target(clMagPhaseToComplexAspenGen ALL
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/clMagPhaseToComplex_aspengen.bash -f=${CMAKE_CURRENT_SOURCE_DIR}/clMagPhaseToComplex_kernel.c && cp ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clMagPhaseToComplex/clMagPhaseToComplex.aspen ${CMAKE_CURRENT_SOURCE_DIR} && rm -rf ${CMAKE_CURRENT_BINARY_DIR}/aspen_output_clMagPhaseToComplex
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/clMagPhaseToComplex_aspengen.bash ${CMAKE_CURRENT_SOURCE_DIR}/clMagPhaseToComplex_kernel.c)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/clMagPhaseToComplex.aspen DESTINATION "${CMAKE_INSTALL_PREFIX}/bin") 

add_dependencies(clMagPhaseToComplexAspenGen clComplextToMagPhaseAspenGen)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

