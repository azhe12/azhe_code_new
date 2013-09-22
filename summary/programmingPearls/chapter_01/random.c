/*Usage: generate k random number from 0 ~ (n - 1)
 * arg1: n
 * arg2: k
 * example: random n k
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
unsigned int randInt(unsigned int a, unsigned int b)
{
	return a + (rand() * RAND_MAX + rand()) % (b - a + 1);
}

void randArray(unsigned int* a, unsigned int n)
{
	unsigned int i, pos, t, j;

	srand(time(NULL));
	for (i = 0; i < n; ++i) 
		a[i] = i;
	for (i = 0; i < n; ++i)
	{
		//printf("random = %d\n", rand());
		//pos = rand()%(n - i) + i;
		j = randInt(i, n - 1);
		t = a[i]; a[i] = a[j]; a[j] = t;
	}
}

#define SIZE	10000000
int main(int argc, char** argv)
{
	unsigned int n, i, k;
	unsigned int *a;
	n = atoi(argv[1]);
	k = atoi(argv[2]);
	a = malloc(sizeof(int) * n);
	randArray(a, n);
	for (i = 0; i < k; i++)
		printf("%d\n", a[i]);
}
