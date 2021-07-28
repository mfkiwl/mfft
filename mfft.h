#pragma once
#include <stdbool.h>
#include <complex.h>

// *** all dimensions must be a power of two ***
void fast_fourier_transform(float complex* data, int len, int stride, bool inverse);

static inline void fft(float complex* data, int len) {
    fast_fourier_transform(data, len, 1, false);
}

static inline void ifft(float complex* data, int len) {
    fast_fourier_transform(data, len, 1, true);
}

void fft_2d(float complex* data, int x_len, int y_len, bool inverse);
