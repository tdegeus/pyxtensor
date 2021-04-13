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
    setup_requires=['pybind11', 'pyxtensor'],
    cmdclass={'build_ext': pyxtensor.BuildExt},
    zip_safe=False,
)
