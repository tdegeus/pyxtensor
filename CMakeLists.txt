
cmake_minimum_required(VERSION 3.0)

# Options
# =======

project(pyxtensor)

# Internals
# =========

set(PYXTENSOR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Version
# =======

file(STRINGS "${PYXTENSOR_INCLUDE_DIR}/${PROJECT_NAME}/pyxtensor.hpp" pyxtensor_version_defines
     REGEX "#define PYXTENSOR_VERSION_(MAJOR|MINOR|PATCH)")

foreach(ver ${pyxtensor_version_defines})
    if(ver MATCHES "#define PYXTENSOR_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(PYXTENSOR_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()

set(${PROJECT_NAME}_VERSION
    ${PYXTENSOR_VERSION_MAJOR}.${PYXTENSOR_VERSION_MINOR}.${PYXTENSOR_VERSION_PATCH})

message(STATUS "Building pyxtensor v${${PROJECT_NAME}_VERSION}")

# Build
# =====

set(PYXTENSOR_HEADERS
  ${PYXTENSOR_INCLUDE_DIR}/${PROJECT_NAME}/pyxtensor.hpp
  ${PYXTENSOR_INCLUDE_DIR}/${PROJECT_NAME}/pybind11_xarray.hpp
  ${PYXTENSOR_INCLUDE_DIR}/${PROJECT_NAME}/pybind11_xtensor.hpp
  ${PYXTENSOR_INCLUDE_DIR}/${PROJECT_NAME}/pybind11_xtensor_fixed.hpp
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PYXTENSOR_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:include>)

# Installation
# ============

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}-targets)

export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

install(FILES ${PYXTENSOR_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

set(PYXTENSOR_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
    STRING "install path for ${PROJECT_NAME}Config.cmake")

configure_package_config_file("${PROJECT_NAME}Config.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${PYXTENSOR_CMAKECONFIG_INSTALL_DIR})

# pyxtensor is header-only and does not depend on the architecture.
# Remove CMAKE_SIZEOF_VOID_P from pyxtensorConfigVersion.cmake so that an pyxtensorConfig.cmake
# generated for a 64 bit target can be used for 32 bit targets and vice versa.
set(_PYXTENSOR_CMAKE_SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P})
unset(CMAKE_SIZEOF_VOID_P)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
set(CMAKE_SIZEOF_VOID_P ${_PYXTENSOR_CMAKE_SIZEOF_VOID_P})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${PYXTENSOR_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${PYXTENSOR_CMAKECONFIG_INSTALL_DIR})

configure_file(${PROJECT_NAME}.pc.in
               "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
                @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig/")
