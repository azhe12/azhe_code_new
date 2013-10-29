/*Note: print prime in [0, n]
 *arg1: range
 *Usage: ./prime 100
 * */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int x)
{
	int i, j;
	if (x < 2)
		return 0;
	else if (x == 2)
		return 1;
	else {
		for (i = 2; i <= sqrt(x); i++) {
			if (x % i == 0)
				return 0;
		}
		return 1;
	}
}

int main(int argc, char** argv)
{
	int range, i, n = 0;
	/*printf("enter range number:\n");*/
	/*scanf("%d", &range);*/

	if (argv[1] == NULL) {
		printf("arg1 should not be null!\n");
		return -1;
	}
	
	range = atoi(argv[1]);
	if (range < 2) {
		printf("no prime in [0, %d]!\n", range);
		return -1;
	}

	for (i = 2; i < range; i++) {
		if (isPrime(i)) {
			printf("%d\n", i);
			n++;
		}
	}
	if (n > 0)
		return 0;
	else
		return -1;
}
