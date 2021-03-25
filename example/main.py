import example
import numpy as np
import sys

d = np.arange(25).reshape(5, 5)

assert np.allclose(2.0 * d, example.arrayTimesTwo(d))
assert np.allclose(2.0 * d, example.tensorTimesTwo(d))

if sys.platform != 'win32':
    assert np.allclose(2.0 * d, example.fixedTimesTwo(d))
