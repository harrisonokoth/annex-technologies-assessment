#include <stdio.h>
#include <math.h>

long pthFactor(long n, long p) {
    long long N = n; // long long for large numbers
    long long factors1[100000]; // array for small factors
    long long factors2[100000]; // for large factors
    long count1 = 0, count2 = 0;
    long long i;
    long long sqrtN = (long long)sqrt((double)N);
    for (i = 1; i <= sqrtN; i++) {
        if (N % i == 0) {
            factors1[count1++] = i;
            if (i != N / i) {
                factors2[count2++] = N / i;
            }
        }
    }
    long total = count1 + count2;
    if (p > total) return 0;
    if (p <= count1) {
        return (long)factors1[p-1];
    } else {
        // p-th smallest from the end of factors2 (which is in descending order)
        // index in factors2: total - p
        return (long)factors2[total - p];
    }
}