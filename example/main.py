import example
import numpy as np

d = np.arange(25).reshape(5, 5)

assert np.allclose(2.0 * d, example.arrayTimesTwo(d))
assert np.allclose(2.0 * d, example.tensorTimesTwo(d))
assert np.allclose(2.0 * d, example.fixedTimesTwo(d))
