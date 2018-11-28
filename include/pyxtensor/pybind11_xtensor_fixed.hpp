/* =================================================================================================

(c - MIT) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/pyxtensor

================================================================================================= */

#ifndef PYXTENSOR_PYBIND11_XTENSOR_FIXED_HPP
#define PYXTENSOR_PYBIND11_XTENSOR_FIXED_HPP

#include "pyxtensor.hpp"

namespace py = pybind11;

namespace pybind11 {
namespace detail {

// =================================================================================================
// type caster: xt::xtensor_fixed <-> NumPy-array
// =================================================================================================

template<typename T, typename S> struct type_caster<xt::xtensor_fixed<T,S>>
{
public:

  using tensor = xt::xtensor_fixed<T,S>;

  PYBIND11_TYPE_CASTER(tensor, _("xt::xtensor_fixed<T,S>"));

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

    // - dimension of the input array (rank, number of indices)
    auto dimension = buf.ndim();
    // - check
    if ( dimension < 1 ) return false;

    // - shape of the input array
    std::vector<size_t> shape(dimension);
    // - copy
    for ( ssize_t i = 0 ; i < dimension ; ++i ) shape[i] = buf.shape()[i];

    // - temporary variable to check of shape: really not elegant, should be improved
    xt::xtensor_fixed<T,S> tmp = xt::empty<T>(shape);
    // - check shape
    for ( size_t i = 0 ; i < shape.size() ; ++i ) if ( tmp.shape()[i] != shape[i] ) return false;

    // - all checks passed : create the proper C++ variable
    value = xt::empty<T>(shape);
    // - copy all data
    std::copy(buf.data(), buf.data()+buf.size(), value.begin());

    // - signal successful variable creation
    return true;
  }

  // C++ -> Python
  // -------------

  static py::handle cast(const xt::xtensor_fixed<T,S>& src, py::return_value_policy, py::handle)
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
