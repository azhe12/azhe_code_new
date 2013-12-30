/* azhe 2013.12.16
 * 时间测量
 * */
#include <stdio.h>
#include <time.h>
#include <math.h>
#define N       10000
#define TRIALS  5

#define M(op, n, trials) {      \
    int trial, i = 0, j = 0;    \
    long start = 0, elapse = 0, sum_loop = 0, sum_trial = 0;                  \
	printf("%s\t", #op);        \
    for (trial = 0; trial < trials; trial++) {  \
        sum_loop = 0;                           \
        start = clock();                \
	    for (i = 0; i < n; i++) {               \
	        for (j = 0; j < n; j++)             \
	            op;                             \
	    }                                       \
        sum_loop += clock() - start;    \
        printf("%f\t", (1e9 * sum_loop / CLOCKS_PER_SEC) );  \
        sum_trial += sum_loop;                  \
    }                                           \
    printf("average: %f\t\n", (1e9 * sum_trial) / (trials * n * n * CLOCKS_PER_SEC));    \
}
int main()
{
    int a = 10, b = 5, c = 20;
    M(a + b, N, TRIALS)
    M(a / b, N, TRIALS)
    M(a % b, N, TRIALS)
    M(sqrt(a), N, TRIALS)
    return 0;
}
