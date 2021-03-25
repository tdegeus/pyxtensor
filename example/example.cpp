#include <xtensor/xarray.hpp>
#include <xtensor/xtensor.hpp>
#ifndef _WIN32
#include <xtensor/xfixed.hpp> // has issues in Windows
#endif
#include <pyxtensor/pyxtensor.hpp>

xt::xarray<double> arrayTimesTwo(const xt::xarray<double>& a)
{
    return 2.0 * a;
}

xt::xtensor<double, 2> tensorTimesTwo(const xt::xtensor<double, 2>& a)
{
    return 2.0 * a;
}

#ifndef _WIN32
xt::xtensor_fixed<double, xt::xshape<5, 5>> fixedTimesTwo(const xt::xtensor_fixed<double, xt::xshape<5, 5>>& a)
{
    return 2.0 * a;
}
#endif

namespace py = pybind11;

PYBIND11_MODULE(example, m)
{
    m.def("arrayTimesTwo", &arrayTimesTwo);
    m.def("tensorTimesTwo", &tensorTimesTwo);
#ifndef _WIN32
    m.def("fixedTimesTwo", &fixedTimesTwo);
#endif
}
