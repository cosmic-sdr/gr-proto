# - Find OpenARC executable and runtime library

# This script defines the following variables:
# OpenARC_BIN_DIR        - Location of OpenARC executable directory.
# OpenARC_INCLUDE_DIR     - Location of OpenARC's include directory.
# OpenARC_LIBRARIES       - OpenARC's libraries
# OpenARC_FOUND           - True if OpenARC has been located
#
# You need to set the envioronment variable openarcinstall to the OpenARC 
# install directory prior to calling this script.
#
#=============================================================================
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#=============================================================================

IF(OpenARC_INCLUDE_DIR)
  # Already in cache, be silent
  set (OpenARC_FIND_QUIETLY TRUE)
ENDIF (OpenARC_INCLUDE_DIR)

IF($ENV{OPENARC_ARCH} MATCHES 0)
	IF($ENV{OPENARC_PROFILE} MATCHES 1)
    	set(OPENARCRUNTIME "openaccrt_cudapf")
	ELSE($ENV{OPENARC_PROFILE} MATCHES 1)
    	set(OPENARCRUNTIME "openaccrt_cuda")
	ENDIF($ENV{OPENARC_PROFILE} MATCHES 1)
ELSE ($ENV{OPENARC_ARCH} MATCHES 0)
	IF($ENV{OPENARC_PROFILE} MATCHES 1)
    	set(OPENARCRUNTIME "openaccrt_openclpf")
	ELSE($ENV{OPENARC_PROFILE} MATCHES 1)
    	set(OPENARCRUNTIME "openaccrt_opencl")
	ENDIF($ENV{OPENARC_PROFILE} MATCHES 1)
ENDIF ($ENV{OPENARC_ARCH} MATCHES 0)

FIND_PATH(_OpenARC_INCLUDE_DIR
    NAMES openaccrt.h openacc.h
	PATHS $ENV{openarcinstall}/openarcrt
    DOC "openarc Include directory")

FIND_PATH(_OpenARC_BIN_DIR
    NAMES openarc
	PATHS $ENV{openarcinstall}/bin
    DOC "openarc Bin directory")

FIND_LIBRARY(_OpenARC_LIBRARY
    NAMES ${OPENARCRUNTIME}
    PATHS $ENV{openarcinstall}/openarcrt)

SET(OpenARC_BIN_DIR ${_OpenARC_BIN_DIR})
SET(OpenARC_INCLUDE_DIR ${_OpenARC_INCLUDE_DIR})
SET(OpenARC_LIBRARIES ${_OpenARC_LIBRARY})

# MESSAGE(STATUS,"_OpenARC_INCLUDE_DIR: ${_OpenARC_INCLUDE_DIR}")
# MESSAGE(STATUS,"_OpenARC_LIBRARY: ${_OpenARC_LIBRARY}")

# handle the QUIETLY and REQUIRED arguments and set OpenARC_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpenARC DEFAULT_MSG OpenARC_LIBRARIES OpenARC_INCLUDE_DIR)
MARK_AS_ADVANCED(OpenARC_LIBRARIES OpenARC_INCLUDE_DIR)


