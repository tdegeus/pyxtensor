/* =================================================================================================

(c - MIT) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/pyxtensor

================================================================================================= */

#ifndef PYXTENSOR_PYBIND11_XARRAY_HPP
#define PYXTENSOR_PYBIND11_XARRAY_HPP

#include "pyxtensor.hpp"

namespace py = pybind11;

namespace pybind11 {
namespace detail {

// =================================================================================================
// type caster: xt::xarray <-> NumPy-array
// =================================================================================================

template<typename T> struct type_caster<xt::xarray<T>>
{
public:

  using tensor = xt::xarray<T>;

  PYBIND11_TYPE_CASTER(tensor, _("xt::xarray<T>"));

  // Python -> C++
  // -------------

  bool load(py::handle src, bool convert)
  {
    // - basic pybind11 check
    if ( !convert && !py::array_t<T>::check_(src) ) return false;

    // - storage requirements : contiguous and row-major storage from NumPy
    auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
    // - check
    if ( !buf ) return false;

    // - get dimension of the input array (rank, number of indices)
    auto N = buf.ndim();
    // - check
    if ( N < 1 ) return false;

    // - shape of the input array
    std::vector<size_t> shape(N);
    // - copy
    for ( ssize_t i = 0 ; i < N ; ++i ) shape[i] = buf.shape()[i];

    // - all checks passed : create the proper C++ variable
    value = xt::empty<T>(shape);
    // - copy all data
    std::copy(buf.data(), buf.data()+buf.size(), value.begin());

    // - signal successful variable creation
    return true;
  }

  // C++ -> Python
  // -------------

  static py::handle cast(const xt::xarray<T>& src, py::return_value_policy, py::handle)
  {
    // - get shape and strides
    auto xshape   = src.shape();
    auto xstrides = src.strides();

    // - convert to vector
    std::vector<size_t> shape(xshape.begin(), xshape.end());
    std::vector<size_t> strides(xstrides.begin(), xstrides.end());

    // - convert strides to bytes
    for ( auto &i : strides ) i *= sizeof(T);

    // - create Python variable (all variables are copied)
    py::array a(std::move(shape), std::move(strides), src.begin());

    // - release variable to Python
    return a.release();
  }
};

// =================================================================================================

}} // namespace pybind11::detail

// -------------------------------------------------------------------------------------------------

#endif
