INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_COSMIC cosmic)

FIND_PATH(
    COSMIC_INCLUDE_DIRS
    NAMES cosmic/api.h
    HINTS $ENV{COSMIC_DIR}/include
        ${PC_COSMIC_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    COSMIC_LIBRARIES
    NAMES gnuradio-cosmic
    HINTS $ENV{COSMIC_DIR}/lib
        ${PC_COSMIC_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(COSMIC DEFAULT_MSG COSMIC_LIBRARIES COSMIC_INCLUDE_DIRS)
MARK_AS_ADVANCED(COSMIC_LIBRARIES COSMIC_INCLUDE_DIRS)

