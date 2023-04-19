Now fully covered in xtensor-python

# pyxtensor

[![CI](https://github.com/tdegeus/pyxtensor/workflows/CI/badge.svg)](https://github.com/tdegeus/pyxtensor/actions)
[![Travis](https://travis-ci.org/tdegeus/pyxtensor.svg?branch=master)](https://travis-ci.org/tdegeus/pyxtensor)
[![Appveyor](https://ci.appveyor.com/api/projects/status/0s6ytkty29f110ks?svg=true)](https://ci.appveyor.com/project/tdegeus/pyxtensor)
[![Conda Version](https://img.shields.io/conda/vn/conda-forge/pyxtensor.svg)](https://anaconda.org/conda-forge/pyxtensor)

>   **Disclaimer**
>   
>   This library is free to use under the [MIT](https://github.com/tdegeus/pyxtensor/blob/master/LICENSE). Any additions are very much appreciated, in terms of suggested functionality, code, documentation, testimonials, word-of-mouth advertisement, etc. Bug reports or feature requests can be filed on [GitHub](https://github.com/tdegeus/pyxtensor). As always, the code comes with no guarantee. None of the developers can be held responsible for possible mistakes.
>   
>   Download: [.zip file](https://github.com/tdegeus/pyxtensor/zipball/master) | [.tar.gz file](https://github.com/tdegeus/pyxtensor/tarball/master).
>   
>   (c - [GPLv3](https://github.com/tdegeus/pyxtensor/blob/master/LICENSE)) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | [github.com/tdegeus/pyxtensor](https://github.com/tdegeus/pyxtensor)
   
## Contents

<!-- MarkdownTOC -->

- [Introduction](#introduction)
- [Getting pyxtensor](#getting-pyxtensor)
  - [Using conda](#using-conda)
  - [Using pip \(Python only\)](#using-pip-python-only)
  - [From source](#from-source)
- [Usage](#usage)
  - [pybind11 module](#pybind11-module)
  - [Compile project using Python](#compile-project-using-python)
  - [Compile project using CMake & Python](#compile-project-using-cmake--python)

<!-- /MarkdownTOC -->

## Introduction

This library provides details for [pybind11](https://github.com/pybind/pybind11) such that an interface to NumPy arrays is automatically provided when including a function that takes any of the [xtensor](https://github.com/QuantStack/xtensor) classes as (return) argument(s). 

> The behaviour is distinctly different from [xtensor-python](https://github.com/QuantStack/xtensor-python). The latter 'maps' NumPy arrays to a so-called `xt::pyarray` giving direct memory access to it. In contrast, *pyxtensor* copies the NumPy object to a `xt::xarray` or `xt::xtensor` and vice versa. This results in a simpler usage in which a C++ library can be exposed without any wrapper functions, however, with the disadvantage of using copies (that cost time, and that disallow in-place modifications).

## Getting pyxtensor

There are two ways of practically using *pyxtensor*. One way is to 'install' the C++ headers somewhere and use CMake or pkg-config to find the C++ headers. The other way is to 'install' the Python library that comes with *pyxtensor* and let it 'install' the C++ headers in the correct Python folder, and use Python to find the C++ headers. 

### Using conda

```bash
conda install -c conda-forge pyxtensor
```

### Using pip (Python only)

```bash
pip install pyxtensor
```

### From source

```bash
# Download pyxtensor
git checkout https://github.com/tdegeus/pyxtensor.git
cd pyxtensor

# For Python use
python setup.py install

# For CMake or pkg-config use
cmake .
make install
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

[download "example.cpp"](./examples/cmake-build/example.cpp)

As observed the pybind11 wrapper immediately acts on the xtensor objects. 

### Compile project using Python

Using the *pyxtensor* Python module the `setup.py` can be as follows

```python
from setuptools import setup, Extension

import pybind11
import pyxtensor

ext_modules = [
    Extension(
        'example',
        ['example.cpp'],
        include_dirs=[
            pyxtensor.find_pyxtensor(),
            pyxtensor.find_pybind11(),
            pyxtensor.find_xtensor()],
        language='c++'
    ),
]

setup(
    name='example',
    description='Short description',
    long_description='Long description',
    version='0.0.1',
    license='MIT',
    author='Tom de Geus',
    author_email='...',
    url='https://github.com/tdegeus/pyxtensor',
    ext_modules=ext_modules,
    setup_requires=['pybind11', 'pyxtensor'],
    cmdclass={'build_ext': pyxtensor.BuildExt},
    zip_safe=False,
)
```

[download "setup.py"](./examples/cmake-build/setup.py)

Compilation can then proceed using 

```bash
python setup.py build
python setup.py install
```

or 

```bash
python -m pip install . -vvv
```

>  For certain xtensor-based codes xsimd is advisable. To enable one could do the following instead:
>  
>  
>  ```python
>  from setuptools import setup, Extension
>  
>  import pybind11
>  import pyxtensor
>  
>  include_dirs = [
>      pyxtensor.find_pyxtensor(),
>      pyxtensor.find_pybind11(),
>      pyxtensor.find_xtensor(),
>      pyxtensor.find_xtl()]
>  
>  build = pyxtensor.BuildExt
>  
>  xsimd = pyxtensor.find_xsimd()
>  if xsimd:
>      if len(xsimd) > 0:
>          include_dirs += [xsimd]
>          build.c_opts['unix'] += ['-march=native', '-DXTENSOR_USE_XSIMD']
>          build.c_opts['msvc'] += ['/DXTENSOR_USE_XSIMD']
>  
>  ext_modules = [
>      Extension(
>          'example',
>          ['example.cpp'],
>          include_dirs = include_dirs,
>          language = 'c++')
>  ]
>  
>  setup(
>    name='example',
>    description='Short description',
>    long_description='Long description',
>    version='0.0.1',
>    license='MIT',
>    author='Tom de Geus',
>    author_email='...',
>    url='https://github.com/...',
>    ext_modules=ext_modules,
>    setup_requires=['pybind11', 'pyxtensor'],
>    cmdclass={'build_ext': build},
>    zip_safe=False)
>  ```

### Compile project using CMake & Python

Using *pyxtensor* the `CMakeLists.txt` can be as follows

```cmake
cmake_minimum_required(VERSION 3.4...3.18)
project(example)

find_package(pybind11 CONFIG REQUIRED)
find_package(pyxtensor REQUIRED)
find_package(xtensor REQUIRED)

pybind11_add_module(example example.cpp)

target_link_libraries(example PUBLIC
    pybind11::module
    pyxtensor
    xtensor::optimize)

# MYVERSION_INFO is defined by setup.py and passed into the C++ code as a define (VERSION_INFO) here
target_compile_definitions(example PRIVATE VERSION_INFO=${MYVERSION_INFO})
```

[download "CMakeLists.txt"](./examples/cmake-build/CMakeLists.txt)

with the corresponding `setup.py`:

```python
import pyxtensor
from setuptools import setup, Extension

setup(
    name='example',
    description='Short description',
    long_description='Long description',
    version='0.0.1',
    license='MIT',
    author='Tom de Geus',
    author_email='...',
    url='https://github.com/tdegeus/pyxtensor',
    ext_modules=[pyxtensor.CMakeExtension("example")],
    cmdclass={"build_ext": pyxtensor.CMakeBuild},
    zip_safe=False,
)
```

[download "setup.py"](./examples/cmake-build/setup.py)

Compilation can then proceed using 

```bash
python setup.py build
python setup.py install
```

or 

```bash
python -m pip install . -vvv
```
