cmake_minimum_required(VERSION 3.1)

project(example_cmake)

find_package(pybind11 REQUIRED)
find_package(pyxtensor REQUIRED)
find_package(xtensor REQUIRED)

add_library(example_cmake example.cpp)

target_link_libraries(example_cmake
    PRIVATE
    pybind11::pybind11
    pyxtensor
    xtensor::optimize)

set_target_properties(example_cmake
    PROPERTIES
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}")
