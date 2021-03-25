#include <xtensor/xarray.hpp>
#include <xtensor/xtensor.hpp>
#include <xtensor/xfixed.hpp>
#include <pyxtensor/pyxarray.hpp>
#include <pyxtensor/pyxtensor.hpp>
#include <pyxtensor/pybind11_xtensor_fixed.hpp>

xt::xarray<double> arrayTimesTwo(const xt::xarray<double>& a)
{
    return 2.0 * a;
}

xt::xtensor<double, 2> tensorTimesTwo(const xt::xtensor<double, 2>& a)
{
    return 2.0 * a;
}

xt::xtensor_fixed<double, xt::xshape<5, 5>> fixedTimesTwo(const xt::xtensor_fixed<double, xt::xshape<5, 5>>& a)
{
    return 2.0 * a;
}

namespace py = pybind11;

PYBIND11_MODULE(example, m)
{
    m.def("arrayTimesTwo", &arrayTimesTwo);
    m.def("tensorTimesTwo", &tensorTimesTwo);
    m.def("fixedTimesTwo", &fixedTimesTwo);
}
