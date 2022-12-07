#include <stdint.h>
#include <stdio.h>
#include <climits>
#include "adpenc/src/adpcm.c"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    double* d_samples = (double*) malloc(sizeof(double) * 28);
    for (int i = 0; i < 28; i++) {
        d_samples[i] = provider.ConsumeFloatingPoint<double>();
    }
    short* four_bit = (short*) malloc(sizeof(short) * 28);
    int predict_nr = provider.ConsumeIntegralInRange<int>(0, 4);
    int shift_factor = provider.ConsumeIntegral<int>();
    pack(d_samples, four_bit, predict_nr, shift_factor);
    free(d_samples);
    free(four_bit);

    return 0;
}