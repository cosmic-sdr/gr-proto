# - Find CUDA executable and runtime library

# This script defines the following variables:
# CUDA_BIN_DIR        - Location of CUDA executable directory.
# CUDA_INCLUDE_DIR     - Location of CUDA's include directory.
# CUDA_LIBRARIES       - CUDA's libraries
# CUDA_FOUND           - True if CUDA has been located
#
# You need to set CUDA_ROOT macro as an argument to the cmake command.
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

IF(CUDA_INCLUDE_DIR)
  # Already in cache, be silent
  set (CUDA_FIND_QUIETLY TRUE)
ENDIF (CUDA_INCLUDE_DIR)

FIND_PATH(_CUDA_INCLUDE_DIR
    NAMES cuda.h cuda_runtime.h
	PATHS ${CUDA_ROOT}/include
    DOC "CUDA include directory")

FIND_PATH(_CUDA_BIN_DIR
    NAMES nvcc
	PATHS ${CUDA_ROOT}/bin
    DOC "CUDA binary directory")

FIND_LIBRARY(_CUDA_LIBRARY
    NAMES cuda
    PATHS ${CUDA_ROOT}/lib64
    DOC "CUDA library directory")

SET(CUDA_BIN_DIR ${_CUDA_BIN_DIR})
SET(CUDA_INCLUDE_DIR ${_CUDA_INCLUDE_DIR})
SET(CUDA_LIBRARIES ${_CUDA_LIBRARY})

# MESSAGE(STATUS,"_CUDA_INCLUDE_DIR: ${_CUDA_INCLUDE_DIR}")
# MESSAGE(STATUS,"_CUDA_LIBRARY: ${_CUDA_LIBRARY}")

# handle the QUIETLY and REQUIRED arguments and set CUDA_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CUDA DEFAULT_MSG CUDA_LIBRARIES CUDA_INCLUDE_DIR)
MARK_AS_ADVANCED(CUDA_LIBRARIES CUDA_INCLUDE_DIR)


