import numpy as np

import PyGCPM


def test_scalar_call_returns_four_float32_arrays():
    output = PyGCPM.GCPM(4.0, 0.0, 0.0, 20010101, 0.0, Kp=1.0)

    assert len(output) == 4
    for density in output:
        assert density.shape == (1,)
        assert density.dtype == np.float32
        assert np.isfinite(density[0])
        assert density[0] >= 0.0


def test_vector_inputs_preserve_length():
    x = np.array([2.0, 4.0, 6.0])
    output = PyGCPM.GCPM(x, np.zeros(3), np.zeros(3), 20010101, 12.0)

    assert all(density.shape == x.shape for density in output)


def test_origin_produces_nan_instead_of_crashing():
    output = PyGCPM.GCPM(0.0, 0.0, 0.0, 20010101, 0.0)

    assert all(np.isnan(density[0]) for density in output)

