cmake_minimum_required(VERSION 3.1)

project(example_cmake)

find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(pybind11 REQUIRED)
find_package(pyxtensor REQUIRED)

add_library(example_cmake example.cpp)

if(MSVC)
    target_compile_options(example_cmake PRIVATE /EHsc /MP /bigobj)
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR
    (CMAKE_CXX_COMPILER_ID MATCHES "Intel" AND NOT WIN32))
    target_compile_options(example_cmake PRIVATE -march=native -std=c++14)
endif()

target_link_libraries(example_cmake
    PRIVATE
    pybind11::pybind11
    xtensor
    pyxtensor)

set_target_properties(example_cmake
    PROPERTIES
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}")
