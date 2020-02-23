#include "mfft.h"
#include <assert.h>

static void bit_reverse_permutation(float complex* data, int len, int stride) {
    for (int i = 0, target = 0; i < len; ++i) {
        if (target > i) {
            float complex tmp = data[i * stride];
            data[i * stride] = data[target * stride];
            data[target * stride] = tmp;
        }
        int mask = len;
        while (target & (mask >>= 1)) {
            target &= ~mask;
        }
        target |= mask;
    }
}

static void compute_butterfly_for_group(float complex* data, int len, int stride, int stage,
        int group, float complex twiddle_factor) {
    for (int pair = group; pair < len; pair += 2 * stage) {
        data[(pair + stage) * stride] *= -twiddle_factor;
        data[(pair + stage) * stride] += data[pair * stride];
        data[pair * stride] += data[pair * stride];
        data[pair * stride] -= data[(pair + stage) * stride];
    }
}

void fast_fourier_transform(float complex* data, int len, int stride, bool inverse) {
    assert(data && len >= 0 && IS_POWER_OF_TWO(len) && stride >= 0);
    bit_reverse_permutation(data, len, stride);
    compute_butterfly_for_group(data, len, stride, 1, 0, 1);
    float complex rotation = inverse ? I : -I;
    for (int stage = 2; stage < (len); stage <<= 1, rotation = csqrtf(rotation)) {
        float complex twiddle_factor = 1;
        for (int group = 0; group < stage; ++group, twiddle_factor *= rotation) {
            compute_butterfly_for_group(data, len, stride, stage, group, twiddle_factor);
        }
    }
    if (inverse) {
        for (int i = 0; i < len; ++i) {
            data[i * stride] /= len;
        }
    }
}

void fft_2d(float complex* data, int x_len, int y_len, bool inverse) {
    for (int x = 0; x < x_len; ++x) {
        fast_fourier_transform(data + x, y_len, x_len, inverse);
    }
    for (int y = 0; y < y_len; ++y, data += x_len) {
        fast_fourier_transform(data, x_len, 1, inverse);
    }
}
