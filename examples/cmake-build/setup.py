import pyxtensor
from setuptools import setup, Extension

setup(
    name='example',
    description='Short description',
    long_description='Long description',
    version='0.0.1',
    license='MIT',
    author='Tom de Geus',
    author_email='tom@geus.me',
    url='https://github.com/tdegeus/pyxtensor',
    ext_modules=[pyxtensor.CMakeExtension("example")],
    cmdclass={"build_ext": pyxtensor.CMakeBuild},
    zip_safe=False,
)
