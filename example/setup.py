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
    author_email='tom@geus.me',
    url='https://github.com/tdegeus/pyxtensor',
    ext_modules=ext_modules,
    install_requires=['pybind11>=2.2.0', 'pyxtensor>=0.1.0'],
    cmdclass={'build_ext': pyxtensor.BuildExt},
    zip_safe=False,
)
