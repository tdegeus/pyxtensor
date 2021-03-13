cmake_minimum_required(VERSION 3.0)

# Basic settings
# ==============

project(pyxtensor)

option(BUILD_TESTS "${PROJECT_NAME} Build tests" OFF)

# Version
# =======

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/include/pyxtensor/pyxtensor.hpp" pyxtensor_version_defines
     REGEX "#define PYXTENSOR_VERSION_(MAJOR|MINOR|PATCH)")

foreach(ver ${pyxtensor_version_defines})
    if(ver MATCHES "#define PYXTENSOR_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
    set(PYXTENSOR_VERSION_${CMAKE_MATCH_1}
        "${CMAKE_MATCH_2}"
        CACHE INTERNAL "")
    endif()
endforeach()

set(PYXTENSOR_VERSION
    ${PYXTENSOR_VERSION_MAJOR}.${PYXTENSOR_VERSION_MINOR}.${PYXTENSOR_VERSION_PATCH})

message(STATUS "Building pyxtensor v${PYXTENSOR_VERSION}")

# Set target
# ==========

if(NOT TARGET xtensor)
    find_package(xtensor REQUIRED)
endif()

add_library(pyxtensor INTERFACE)

target_include_directories(pyxtensor INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(pyxtensor INTERFACE xtensor)

# Installation
# ============

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION include)

install(TARGETS pyxtensor EXPORT pyxtensor-targets)

install(
    EXPORT pyxtensor-targets
    FILE pyxtensorTargets.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/pyxtensor")

set(_PYXTENSOR ${CMAKE_SIZEOF_VOID_P})
unset(CMAKE_SIZEOF_VOID_P)

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/pyxtensorConfigVersion.cmake"
    VERSION ${PYXTENSOR_VERSION}
    COMPATIBILITY AnyNewerVersion)

set(CMAKE_SIZEOF_VOID_P ${_PYXTENSOR})

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/pyxtensorConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/pyxtensorConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/pyxtensor")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/pyxtensor.pc.in"
               "${CMAKE_CURRENT_BINARY_DIR}/pyxtensor.pc" @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pyxtensor.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig/")
