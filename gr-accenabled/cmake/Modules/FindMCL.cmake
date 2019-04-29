# - Find MCL executable and runtime library

# This script defines the following variables:
# MCL_BIN_DIR        - Location of MCL executable directory.
# MCL_INCLUDE_DIR     - Location of MCL's include directory.
# MCL_LIBRARIES       - MCL's libraries
# MCL_MISC_LIBRARIES       - Additional libraries used with MCL libraries
# MCL_FOUND           - True if MCL has been located
#
# You need to set the envioronment variable mclinstallroot to the root directory where 
# MCL libraries and headers are installed.
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

IF(MCL_INCLUDE_DIR)
  # Already in cache, be silent
  set (MCL_FIND_QUIETLY TRUE)
ENDIF (MCL_INCLUDE_DIR)

FIND_PATH(_MCL_INCLUDE_DIR
    NAMES minos.h mcl_accext.h openacc.h
	PATHS $ENV{mclinstallroot}/include
    DOC "MCL Include directory")

FIND_PATH(_MCL_BIN_DIR
    NAMES mcl_sched
	PATHS $ENV{mclinstallroot}/bin
    DOC "MCL Bin directory")

FIND_LIBRARY(_MCL_LIBRARY1
    NAMES mcl 
    PATHS $ENV{mclinstallroot}/lib)

FIND_LIBRARY(_MCL_LIBRARY2
    NAMES mclext
    PATHS $ENV{mclinstallroot}/lib)

FIND_LIBRARY(_MCL_MISC_LIBRARY1
    NAMES rt)

FIND_LIBRARY(_MCL_MISC_LIBRARY2
    NAMES m)

FIND_LIBRARY(_MCL_MISC_LIBRARY3
    NAMES pthread)

SET(MCL_BIN_DIR ${_MCL_BIN_DIR})
SET(MCL_INCLUDE_DIR ${_MCL_INCLUDE_DIR})
LIST(APPEND MCL_LIBRARIES ${_MCL_LIBRARY1})
LIST(APPEND MCL_LIBRARIES ${_MCL_LIBRARY2})
LIST(APPEND MCL_MISC_LIBRARIES ${_MCL_MISC_LIBRARY1})
LIST(APPEND MCL_MISC_LIBRARIES ${_MCL_MISC_LIBRARY2})
LIST(APPEND MCL_MISC_LIBRARIES ${_MCL_MISC_LIBRARY3})

# handle the QUIETLY and REQUIRED arguments and set MCL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MCL DEFAULT_MSG MCL_LIBRARIES MCL_MISC_LIBRARIES MCL_INCLUDE_DIR)
MARK_AS_ADVANCED(MCL_LIBRARIES MCL_MISC_LIBRARIES MCL_INCLUDE_DIR)


