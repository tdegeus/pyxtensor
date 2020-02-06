/*

(c - MIT) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/pyxtensor

*/

#ifndef PYXTENSOR_H
#define PYXTENSOR_H

#include <xtensor/xarray.hpp>
#include <xtensor/xtensor.hpp>
#include <xtensor/xfixed.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

#define PYXTENSOR_VERSION_MAJOR 0
#define PYXTENSOR_VERSION_MINOR 1
#define PYXTENSOR_VERSION_PATCH 3

#define PYXTENSOR_VERSION_AT_LEAST(x,y,z) \
    (PYXTENSOR_VERSION_MAJOR > x || (PYXTENSOR_VERSION_MAJOR >= x && \
    (PYXTENSOR_VERSION_MINOR > y || (PYXTENSOR_VERSION_MINOR >= y && \
                                     PYXTENSOR_VERSION_PATCH >= z))))

#define PYXTENSOR_VERSION(x,y,z) \
    (PYXTENSOR_VERSION_MAJOR == x && \
     PYXTENSOR_VERSION_MINOR == y && \
     PYXTENSOR_VERSION_PATCH == z)

#include "pybind11_xarray.hpp"
#include "pybind11_xtensor.hpp"
#include "pybind11_xtensor_fixed.hpp"

#endif

