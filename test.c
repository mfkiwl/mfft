#include "mfft.h"
#include <stdio.h>
#include <time.h>

#define TEST_SAMPLE_LEN (8)
#define BENCHMARK_ITERATIONS (10000)
#define DATA_LEN (1024)
static float complex data[DATA_LEN];

int main() {
    data[1] = TEST_SAMPLE_LEN;

    ifft(data, TEST_SAMPLE_LEN);

    printf("test input (time domain):\n");
    for (int i = 0; i < TEST_SAMPLE_LEN; ++i) {
        printf("  n %i re %f im %f\n", i, crealf(data[i]), cimagf(data[i]));
    }

    fft(data, TEST_SAMPLE_LEN);

    printf("test output (freq domain):\n");
    for (int i = 0; i < TEST_SAMPLE_LEN; ++i) {
        printf("  n %i re %f im %f\n", i, crealf(data[i]), cimagf(data[i]));
    }

    printf("benchmarking %d point FFT ...\n", DATA_LEN);
    clock_t start_time = clock();

    for (int i = 0; i < BENCHMARK_ITERATIONS; ++i) {
        fft(data, DATA_LEN);
    }

    clock_t end_time = clock();
    printf("  %d iterations took %fs\n", BENCHMARK_ITERATIONS,
            (double) (end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}
