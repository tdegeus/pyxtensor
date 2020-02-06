long_description = '''
This library provides details for pybind11 such that an interface to NumPy arrays is automatically
provided when including a function that takes any of the xtensor classes as (return) argument(s).

Note that this library is simpler but more naive than xtensor-python as arguments are always copies
of the NumPy arrays. This simplifies the Python wrapper code greatly, but comes at the prices of
having to copy.

This library also provides a small Python library that can be used to compile the wrapper code using
a 'setup.py'.
'''

import re
import os
from setuptools import setup

header = open('include/pyxtensor/pyxtensor.hpp', 'r').read()
major = re.split(r'(.*)(\#define PYXTENSOR_VERSION_MAJOR\ )([0-9]+)(.*)', header)[3]
minor = re.split(r'(.*)(\#define PYXTENSOR_VERSION_MINOR\ )([0-9]+)(.*)', header)[3]
patch = re.split(r'(.*)(\#define PYXTENSOR_VERSION_PATCH\ )([0-9]+)(.*)', header)[3]

__version__ = '.'.join([major, minor, patch])

setup(
    name = 'pyxtensor',
    description = 'pybind11 details for xtensor',
    long_description =  long_description,
    keywords = 'C++, C++11, C++14, Python bindings, pybind11, xtensor',
    version = __version__,
    license = 'MIT',
    author = 'Tom de Geus',
    author_email = 'tom@geus.me',
    url = 'https://github.com/tdegeus/pyxtensor',
    packages = ['pyxtensor'],
    headers = [
        'include/pyxtensor/pyxtensor.hpp',
        'include/pyxtensor/pybind11_xarray.hpp',
        'include/pyxtensor/pybind11_xtensor.hpp',
        'include/pyxtensor/pybind11_xtensor_fixed.hpp'],
    install_requires = ['pybind11>=2.2.0'],
)

