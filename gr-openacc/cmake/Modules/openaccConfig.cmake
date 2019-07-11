INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_OPENACC openacc)

FIND_PATH(
    OPENACC_INCLUDE_DIRS
    NAMES openacc/api.h
    HINTS $ENV{OPENACC_DIR}/include
        ${PC_OPENACC_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    OPENACC_LIBRARIES
    NAMES gnuradio-openacc
    HINTS $ENV{OPENACC_DIR}/lib
        ${PC_OPENACC_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OPENACC DEFAULT_MSG OPENACC_LIBRARIES OPENACC_INCLUDE_DIRS)
MARK_AS_ADVANCED(OPENACC_LIBRARIES OPENACC_INCLUDE_DIRS)

