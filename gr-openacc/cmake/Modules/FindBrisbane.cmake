# - Find BRISBANE executable and runtime library

# This script defines the following variables:
# BRISBANE_BIN_DIR        - Location of BRISBANE executable directory.
# BRISBANE_INCLUDE_DIR     - Location of BRISBANE's include directory.
# BRISBANE_LIBRARIES       - BRISBANE's libraries
# BRISBANE_MISC_LIBRARIES       - Additional libraries used with BRISBANE libraries
# BRISBANE_FOUND           - True if BRISBANE has been located
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

IF(BRISBANE_INCLUDE_DIR)
  # Already in cache, be silent
  set (BRISBANE_FIND_QUIETLY TRUE)
ENDIF (BRISBANE_INCLUDE_DIR)

FIND_PATH(_BRISBANE_INCLUDE_DIR
    NAMES brisbane/brisbane_runtime.h
	PATHS $ENV{HOME}/local/include $ENV{HOME}/.local/include $ENV{HOME}/usr/local/include
    DOC "BRISBANE Include directory")

FIND_PATH(_BRISBANE_BIN_DIR
    NAMES brisbane-clc brisbane-hub
	PATHS $ENV{HOME}/local/bin $ENV{HOME}/.local/bin $ENV{HOME}/usr/local/bin
    DOC "BRISBANE Bin directory")

FIND_LIBRARY(_BRISBANE_LIBRARY1
    NAMES brisbane 
	PATHS $ENV{HOME}/local/lib64 $ENV{HOME}/.local/lib64 $ENV{HOME}/usr/local/lib64)

FIND_LIBRARY(_BRISBANE_MISC_LIBRARY1
    NAMES dl)

SET(BRISBANE_BIN_DIR ${_BRISBANE_BIN_DIR})
SET(BRISBANE_INCLUDE_DIR ${_BRISBANE_INCLUDE_DIR})
LIST(APPEND BRISBANE_LIB_LIST ${_BRISBANE_LIBRARY1})
#LIST(GET BRISBANE_LIB_LIST 0 1 BRISBANE_LIBRARIES)
SET(BRISBANE_LIBRARIES ${BRISBANE_LIB_LIST})
LIST(APPEND BRISBANE_MISC_LIB_LIST ${_BRISBANE_MISC_LIBRARY1})
#LIST(GET BRISBANE_MISC_LIB_LIST 0 1 2 BRISBANE_MISC_LIBRARIES)
SET(BRISBANE_MISC_LIBRARIES ${BRISBANE_MISC_LIB_LIST})

# handle the QUIETLY and REQUIRED arguments and set BRISBANE_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BRISBANE DEFAULT_MSG BRISBANE_LIBRARIES BRISBANE_MISC_LIBRARIES BRISBANE_INCLUDE_DIR)
MARK_AS_ADVANCED(BRISBANE_LIBRARIES BRISBANE_MISC_LIBRARIES BRISBANE_INCLUDE_DIR)


