import example
import numpy as np

a = np.arange(5)
b = example.timesTwo(a)

assert np.allclose(2.0 * a, b)
