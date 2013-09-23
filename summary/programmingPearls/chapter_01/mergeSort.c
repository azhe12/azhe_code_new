/*merge sort
 * azhe liu 2013.9.22
 * Read source file from STDIN
 * Output sorted data to STDOUT
 * Usage: cat sourcefile | ./mergeSort
 *
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ARRAY_SIZE	10000000
void mergeSortedNumber(unsigned int * a, unsigned int first, unsigned int mid, unsigned int end, unsigned int *tmp)
{
	//unsigned int * tmp = malloc(ARRAY_SIZE * sizeof(int));
	unsigned int i = first, j = mid + 1, k = 0;
	while ((i <= mid ) && (j <= end )) {
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}
		while (i <= mid)
			tmp[k++] = a[i++];
		while (j <= end)
			tmp[k++] = a[j++];
	for (i = 0; i < k; i++) {
		a[first + i] = tmp[i];
		printf("%d\n", tmp[i]);
	}
	printf(">>>>\n");
}

void mergesort(unsigned int *a, unsigned int bottom, unsigned int top, unsigned int* tmp)
{
	unsigned int mid;
	if (top > bottom) {
		mid = (bottom + top) / 2;
		mergesort(a, bottom, mid, tmp);
		mergesort(a, mid + 1, top, tmp);
		//mergeSortedNumber(a + bottom, mid - bottom + 1, a + mid + 1, top - mid, tmp);
		mergeSortedNumber(a, bottom, mid, top, tmp);
	}
}

void MergeSort(unsigned int* a, unsigned int size)
{
	unsigned int * tmp;
	if ( !(tmp = malloc(ARRAY_SIZE * sizeof(int)))) {
		printf("no memory!\n");
		return;
	}
	mergesort(a, 0, size - 1, tmp);
	free(tmp);
}
int main(int argc, char** argv)
{
	unsigned int n, i = 0;
	unsigned int *a = malloc(sizeof(int) * ARRAY_SIZE);
	while(scanf("%d", &n) != EOF) {
		a[i++] = n;
		printf("input num = %d\n", a[i - 1]);
	}
	//mergeSortedNumber(a, 0, 2, 5);
	//mergeSort(a, );
	MergeSort(a, i);
	free(a);
}
