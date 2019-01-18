/* =================================================================================================

(c - MIT) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/pyxtensor

================================================================================================= */

#ifndef PYXTENSOR_H
#define PYXTENSOR_H

// =================================================================================================

#include <xtensor/xarray.hpp>
#include <xtensor/xtensor.hpp>
#include <xtensor/xfixed.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

// =================================================================================================

#define PYXTENSOR_WORLD_VERSION 0
#define PYXTENSOR_MAJOR_VERSION 0
#define PYXTENSOR_MINOR_VERSION 4

#define PYXTENSOR_VERSION_AT_LEAST(x,y,z) \
  (PYXTENSOR_WORLD_VERSION>x || (PYXTENSOR_WORLD_VERSION>=x && \
  (PYXTENSOR_MAJOR_VERSION>y || (PYXTENSOR_MAJOR_VERSION>=y && \
                                 PYXTENSOR_MINOR_VERSION>=z))))

#define PYXTENSOR_VERSION(x,y,z) \
  (PYXTENSOR_WORLD_VERSION==x && \
   PYXTENSOR_MAJOR_VERSION==y && \
   PYXTENSOR_MINOR_VERSION==z)

// =================================================================================================

// dummy operation that can be use to suppress the "unused parameter" warnings
#define UNUSED(p) ( (void)(p) )

// =================================================================================================

#include "pybind11_xarray.hpp"
#include "pybind11_xtensor.hpp"
#include "pybind11_xtensor_fixed.hpp"

// =================================================================================================

#endif

