cmake_minimum_required(VERSION 3.4...3.18)
project(example)

find_package(pybind11 CONFIG REQUIRED)
find_package(pyxtensor REQUIRED)
find_package(xtensor REQUIRED)

pybind11_add_module(example example.cpp)

target_link_libraries(example PUBLIC
    pybind11::module
    pyxtensor
    xtensor::optimize)

# MYVERSION_INFO is defined by setup.py and passed into the C++ code as a define (VERSION_INFO) here
target_compile_definitions(example PRIVATE VERSION_INFO=${MYVERSION_INFO})
