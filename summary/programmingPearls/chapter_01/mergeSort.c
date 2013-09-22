#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void mergeSortedNumber(unsigned int * a_left, unsigned int size_left, \
		unsigned int * a_right, unsigned int size_right, unsigned int * result)
{
	unsigned int i = 0, j = 0, k = 0;
	while (i < size_left && j < size_right) {
		if (a_left[i] <= a_right[j])
			result[k++] = a_left[i++];
		else
			result[k++] = a_right[j++];
	}
	if (i >= size_left)
		while (j < size_right)
			result[k++] = a_right[j++];
	else if (j >= size_right)
		while (i < size_left)
			result[k++] = a_left[i++];
}

#define ARRAY_SIZE	10000000
int main(int argc, char** argv)
{
	unsigned int n, i = 0;
	unsigned int *a = malloc(sizeof(int) * ARRAY_SIZE);
	while(scanf("%d", &n) != EOF) {
		a[i++] = n;
		printf("input num = %d\n", a[i - 1]);
	}

	free(a);
}
