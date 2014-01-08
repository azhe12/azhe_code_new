/* azhe 2013.12.16
 * 时间测量
 * */
#include <stdio.h>
#include <time.h>
#include <math.h>
#define N       1e9
#define TRIALS  5

#define M(op, n, trials) {      \
    long long trial, i = n, j = n;    \
    long long start = 0, elapse = 0, sum_loop = 0, sum_trial = 0;                  \
	printf("%s\n", #op);        \
    for (trial = 0; trial < trials; trial++) {  \
        i = n;                  \
        j = n;                   \
        sum_loop = 0;                           \
        start = clock();                \
        while (i-- > 0)                 \
            while (j-- > 0)             \
	            op;                             \
        sum_loop = clock() - start;    \
        printf("%e\t", (1e9 * sum_loop * 1.0 / CLOCKS_PER_SEC) ); \
        sum_trial += sum_loop;                  \
    }                                           \
    printf("average: %f\t\n", (1e9 * sum_trial * 1.0) / (trials * n * n * CLOCKS_PER_SEC));    \
}
int main()
{
    int a = 10, b = 5, c = 20;
    int e = 21, f, g;
    int result;
    M(result = a + 10, N, TRIALS)
    M(result = a / 10, N, TRIALS)
    M(result = a % 10, N, TRIALS)
    M(result = sqrt(a), N, TRIALS)

    M(result = e % 10;result = e / 10, N, TRIALS)
    M(result = e % 10, N, TRIALS)
    M(result = e / 10, N, TRIALS)

    M(result = e & 0x0f;result = e >> 4, N, TRIALS)
    M(result = e >> 4, N, TRIALS)
    M(result = e & 0x0f, N, TRIALS)
    return 0;
}
