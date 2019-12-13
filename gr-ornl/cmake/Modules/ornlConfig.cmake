INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_ORNL ornl)

FIND_PATH(
    ORNL_INCLUDE_DIRS
    NAMES ornl/api.h
    HINTS $ENV{ORNL_DIR}/include
        ${PC_ORNL_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    ORNL_LIBRARIES
    NAMES gnuradio-ornl
    HINTS $ENV{ORNL_DIR}/lib
        ${PC_ORNL_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ORNL DEFAULT_MSG ORNL_LIBRARIES ORNL_INCLUDE_DIRS)
MARK_AS_ADVANCED(ORNL_LIBRARIES ORNL_INCLUDE_DIRS)

