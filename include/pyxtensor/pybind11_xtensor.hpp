/* =================================================================================================

(c - MIT) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/pyxtensor

================================================================================================= */

#ifndef PYXTENSOR_PYBIND11_XTENSOR_HPP
#define PYXTENSOR_PYBIND11_XTENSOR_HPP

#include "pyxtensor.hpp"

namespace py = pybind11;

namespace pybind11 {
namespace detail {

// =================================================================================================
// type caster: xt::xtensor <-> NumPy-array
// =================================================================================================

template<typename T, size_t N> struct type_caster<xt::xtensor<T, N>>
{
public:

    using type = xt::xtensor<T, N>;

    PYBIND11_TYPE_CASTER(type, _("numpy.ndarray[") + npy_format_descriptor<T>::name + _("]"));

    // Python -> C++
    // -------------

    bool load(py::handle src, bool convert)
    {
        // - basic pybind11 check
        if (!convert && !py::array_t<T>::check_(src)) {
            return false;
        }

        // - storage requirements : contiguous and row-major storage from NumPy
        auto buf = py::array_t<T, py::array::c_style | py::array::forcecast>::ensure(src);
        // - check
        if (!buf) {
            return false;
        }

        // - check dimension of the input array (rank, number of indices)
        if (buf.ndim() != N) {
            return false;
        }

        // - shape of the input array
        std::array<size_t, N> shape;
        for (size_t i = 0; i < N; ++i) {
            shape[i] = buf.shape()[i];
        }

        // - all checks passed : create the proper C++ variable
        value.resize(shape);
        std::copy(buf.data(), buf.data() + buf.size(), value.begin());

        // - signal successful variable creation
        return true;
    }

    // C++ -> Python
    // -------------

    static py::handle cast(const xt::xtensor<T, N>& src, py::return_value_policy, py::handle)
    {
        // - get shape and strides
        auto xshape = src.shape();
        auto xstrides = src.strides();

        // - convert to vector
        std::vector<size_t> shape(xshape.begin(), xshape.end());
        std::vector<size_t> strides(xstrides.begin(), xstrides.end());

        // - convert strides to bytes
        for (auto& i : strides) {
            i *= sizeof(T);
        }

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
