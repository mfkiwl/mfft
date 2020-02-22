#include <complex.h>

#include "mfft.h"

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

static void fast_fourier_transform_butterfly_group(float complex* data, int len, int stride, int stage, int group, float complex twiddle_factor) { 
    for (int pair = group; pair < len; pair += 2 * stage) {                 
        data[(pair + stage) * stride] *= -twiddle_factor;
        data[(pair + stage) * stride] += data[pair * stride];
        data[pair * stride] += data[pair * stride];
        data[pair * stride] -= data[(pair + stage) * stride];
    }
}

static void fast_fourier_transform(float complex* data, int len, int stride, int inverse) {                                                                                        
    bit_reverse_permutation(data, len, stride);                                             
    fast_fourier_transform_butterfly_group(data, len, stride, 1, 0, 1); 
    float complex rotation = (inverse > 0) ? I : -I;                                         
    for (int stage = 2; stage < (len); stage <<= 1, rotation = csqrtf(rotation)) {
        float complex twiddle_factor = 1;                                                    
        for (int group = 0; group < stage; ++group, twiddle_factor *= rotation) {       
            fast_fourier_transform_butterfly_group(data, len, stride, stage, group, twiddle_factor);                       
        }                                                                                   
    }                                                                                       
    if (inverse > 0) {                                                                      
        for (int i = 0; i < len; ++i) {                                   
            data[i * stride] /= len;
        }                                                                                   
    }                                                                                       
}

int main() {
    return 0;
}
