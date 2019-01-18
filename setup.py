
import re, os
from setuptools import setup

header = open('include/pyxtensor/pyxtensor.hpp','r').read()
world  = re.split(r'(.*)(\#define PYXTENSOR_WORLD_VERSION\ )([0-9]+)(.*)',header)[3]
major  = re.split(r'(.*)(\#define PYXTENSOR_MAJOR_VERSION\ )([0-9]+)(.*)',header)[3]
minor  = re.split(r'(.*)(\#define PYXTENSOR_MINOR_VERSION\ )([0-9]+)(.*)',header)[3]

__version__ = '.'.join([world,major,minor])

setup(
  name             = 'pyxtensor',
  description      = 'pybind11 details for xtensor.',
  long_description = open('README.md').read(),
  keywords         = 'C++, C++11, C++14, Python bindings, pybind11, xtensor',
  version          = __version__,
  license          = 'MIT',
  author           = 'Tom de Geus',
  author_email     = 'tom@geus.me',
  url              = 'https://github.com/tdegeus/pyxtensor',
  packages         = ['pyxtensor'],
  headers          = [
    'include/pyxtensor/pyxtensor.hpp',
    'include/pyxtensor/pybind11_xarray.hpp',
    'include/pyxtensor/pybind11_xtensor.hpp',
    'include/pyxtensor/pybind11_xtensor_fixed.hpp',
  ],
  install_requires = ['pybind11>=2.2.0'],
)

