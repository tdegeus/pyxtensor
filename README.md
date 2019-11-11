# pyxtensor

<!-- MarkdownTOC -->

- [Introduction](#introduction)
- [Getting pyxtensor](#getting-pyxtensor)
  - [Using pip](#using-pip)
  - [Using conda](#using-conda)
  - [From source](#from-source)
- [Usage](#usage)
  - [pybind11 module](#pybind11-module)
  - [Compile project using `setup.py`](#compile-project-using-setuppy)
- [Develop](#develop)

<!-- /MarkdownTOC -->

## Introduction

This library provides details for [pybind11](https://github.com/pybind/pybind11) such that an interface to NumPy arrays is automatically provided when including a function that takes any of the [xtensor](https://github.com/QuantStack/xtensor) classes as (return) argument(s). 

> The behaviour is distinctly different from [xtensor-python](https://github.com/QuantStack/xtensor-python). The latter 'maps' NumPy arrays to a so-called `xt::pyarray` giving direct memory access to it. In contrast, [pyxtensor](https://github.com/tdegeus/pyxtensor) copies the NumPy object to a `xt::array` or `xt::tensor` and vice versa. This results in a simpler usage in which a C++ library can be exposed without any wrapper functions, however, with the disadvantage of using copies (that cost time, and that disallow in-place modifications).

## Getting pyxtensor

### Using pip

```bash
pip install pyxtensor
```

### Using conda

```bash
conda install -c conda-forge pyxtensor
```

### From source

```bash
git checkout https://github.com/tdegeus/pyxtensor.git
cd pyxtensor
python setup.py install
```

## Usage

### pybind11 module

Consider the following example:

```cpp
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
```

As observed the [pybind11](https://github.com/pybind/pybind11) wrapper immediately acts on the [xtensor](https://github.com/QuantStack/xtensor) objects. See [pybind11_examples](https://github.com/tdegeus/pybind11_examples) for compilation strategies.

### Compile project using `setup.py`

Using the [pyxtensor](https://github.com/tdegeus/pyxtensor) Python module the `setup.py` of a [pybind11](https://github.com/pybind/pybind11) project can be as follows

```python
from setuptools import setup, Extension

import sys, re
import setuptools
import pybind11
import pyxtensor

ext_modules = [
  Extension(
    'ModuleName',
    ['path/to/pybind11/interface.cpp'],
    include_dirs=[
      pybind11.get_include(False),
      pybind11.get_include(True),
      pyxtensor.get_include(False),
      pyxtensor.get_include(True),
      pyxtensor.find_xtensor(),
      pyxtensor.find_xtl(),
      pyxtensor.find_eigen(),
    ],
    language='c++'
  ),
]

setup(
  name             = 'ModuleName',
  description      = 'Short description',
  long_description = 'Long description',
  version          = 'vX.X.X',
  license          = 'MIT',
  author           = 'Tom de Geus',
  author_email     = '...',
  url              = 'https://github.com/...',
  ext_modules      = ext_modules,
  install_requires = ['pybind11>=2.2.0', 'pyxtensor>=0.0.1'],
  cmdclass         = {'build_ext': pyxtensor.BuildExt},
  zip_safe         = False,
)
```

Compilation can then proceed using 

```bash
python setup.py build
python setup.py install
```

## Develop

1.  Update the version number as follows in `include/pyxtensor/pyxtensor.hpp``. 

2.  Upload the changes to GitHub and create a new release there (with the correct version number).

3.  Upload the package to PyPi:

    ```bash
    python setup.py bdist_wheel --universal
    twine upload dist/*
    ```

4.  Update the package at conda-forge.


