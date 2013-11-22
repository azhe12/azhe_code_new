/*merge sort
 * azhe liu 2013.9.22
 * Read source file from STDIN
 * Output sorted data to STDOUT
 * Usage: cat sourcefile | ./mergeSort -q
 * arg1: (default -m)
 *		-m  mergesort
 *		-q quicksort
 *
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ARRAY_SIZE	10000000
#ifdef DEBUG
	#define pr_debug(...) printf(...)
#else
	#define pr_debug(...)
#endif

void mergeSortedNumber(int * a, int first, int mid, int end, int *tmp)
{
	//int * tmp = malloc(ARRAY_SIZE * sizeof(int));
	int i = first, j = mid + 1, k = 0;
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
		pr_debug("%d\n", tmp[i]);
	}
	pr_debug(">>>>\n");
}

void mergesort(int *a, int bottom, int top, int* tmp)
{
	int mid;
	if (top > bottom) {
		mid = (bottom + top) / 2;
		mergesort(a, bottom, mid, tmp);
		mergesort(a, mid + 1, top, tmp);
		//mergeSortedNumber(a + bottom, mid - bottom + 1, a + mid + 1, top - mid, tmp);
		mergeSortedNumber(a, bottom, mid, top, tmp);
	}
}

void MergeSort(int* a, int size)
{
	int * tmp;
	if ( !(tmp = malloc(ARRAY_SIZE * sizeof(int)))) {
		printf("no memory!\n");
		return;
	}
	mergesort(a, 0, size - 1, tmp);
	free(tmp);
}

int QuickSort(int* a, int start, int end, int pivot)
{
	int i, j, tmp, p, x;
	int k;
#if 0
	printf("----------------\n");
	for (i = start; i <= end; i++)
		printf("%d ", a[i]);
	printf("\n");
	printf("s: %d, e: %d p: %d\n", start, end, pivot);
#endif
	if (start >= end) /*end*/
		return 0;
	else {
		x = a[pivot];
		j = end;
		i = start;
		while (j > i) {
			for (; (a[j] >= x) && (j > i); j--);
			if (j == i)
				break;
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
#if 0
		for (k = start; k <= end; k++)
			printf("%d ", a[k]);

		printf("right i: %d j: %d\n", i, j);
#endif
			for (;(a[i] <= x) && (i < j); i++);
			if (i == j)
				break;
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
#if 0
		for (k = start; k <= end; k++)
			printf("%d ", a[k]);
			
		printf("left i: %d j: %d\n", i, j);
		printf("+++++++\n");
#endif
		}
		if (a[i] == x) /*new pivot*/
			p = i;
		else
			p = j;

		QuickSort(a, start, p, start);
		QuickSort(a, p + 1, end, p + 1);
	}
	return 0;
}
void quickSort(int* a, int size)
{
	/*int p = 0;*/
	QuickSort(a, 0, size - 1, 0);
}
int main(int argc, char** argv)
{
	int n, i = 0, size;
	int *a = malloc(sizeof(int) * ARRAY_SIZE);
	int flag;

	if (argv[1] == NULL) {
		printf("arg1 should not be null! -m or -q\n");
		return -1;
	}
	if (strcmp(argv[1], "-m") == 0)
		flag = 1;
	else if (strcmp(argv[1], "-q") == 0)
		flag = 2;
	else {
		printf("arg1 should be  -m or -q\n");
		return -1;
	}
	
	/*read source from STDIN*/
	while(scanf("%d", &n) != EOF) {
		a[i++] = n;
		pr_debug("input num = %d\n", a[i - 1]);
	}
	size = i;
	switch (flag) {
		case 1:
			MergeSort(a, size);
			break;
		case 2:
			quickSort(a, size);
			break;
		default:
			;
	}
	for (i = 0; i < size; i++)
		printf("%d\n", a[i]);
	free(a);
}
