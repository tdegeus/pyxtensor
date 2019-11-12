#include <xtensor/xarray.hpp>
#include <pyxtensor/pyxtensor.hpp>

xt::xarray<double> timesTwo(const xt::xarray<double>& a)
{
    return 2. * a;
}

namespace py = pybind11;

PYBIND11_MODULE(example, m)
{
    m.def("timesTwo", &timesTwo);
}
