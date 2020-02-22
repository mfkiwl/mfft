# mFFT 
A minimalist and portable Fast Fourier Transform library for small applications.
- Contains forward FFT, inverse FFT, and separatable 2D FFT
- Radix 2 decimation-in-time implementation
- ~50 lines of core code
- portable, self-contained, C99 compliant

## Usage
self-explanitory, see [mfft.h](./mfft.h)
```C
// example 
#include "mfft.h"
float complex data[1024]; // requires size to be 2^n 
fft(data, 1024);          // performs FFT inplace
```
## Demo
```bash
make
./build/test
```
