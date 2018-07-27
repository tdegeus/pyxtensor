desc = '''
Extra functions for xtensor.
'''

import re, os
from setuptools import setup

header = open('include/pyxtensor/pyxtensor.hpp','r').read()
world  = re.split(r'(.*)(\#define PYXTENSOR_WORLD_VERSION\ )([0-9]+)(.*)',header)[3]
major  = re.split(r'(.*)(\#define PYXTENSOR_MAJOR_VERSION\ )([0-9]+)(.*)',header)[3]
minor  = re.split(r'(.*)(\#define PYXTENSOR_MINOR_VERSION\ )([0-9]+)(.*)',header)[3]

__version__ = '.'.join([world,major,minor])

setup(
  name             = 'pyxtensor',
  description      = 'Extra functions for xtensor.',
  long_description = desc,
  keywords         = 'C++, C++11, Python bindings, pybind11',
  version          = __version__,
  license          = 'MIT',
  author           = 'Tom de Geus',
  author_email     = 'tom@geus.me',
  url              = 'https://github.com/tdegeus/pyxtensor',
  packages         = ['pyxtensor'],
  headers          = [
    'include/pyxtensor/pyxtensor.hpp',
    'include/pyxtensor/pybind11_xtensor.hpp',
    'include/pyxtensor/pybind11_xtensor_fixed.hpp',
  ],
  install_requires = ['pybind11>=2.2.0'],
)

