#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "baseLib.h"

using namespace std;
/*read STDIN number to array
 *return number of input
 * */
int readStdinNumToArray(int* a, int size)
{
	int i = 0, num;
	while (scanf("%d", &num) != EOF) {
		if (i < size)
			a[i++] = num;
		else {
			printf("input exceed max length: %u\n", size);
			break;
		}
	}
	return i;
}
void mergeSortedNumber(void * a, int first, int mid, int end, int width, void *tmp, CMP compare)
{
	int i = first, j = mid + 1, k = 0;
	while ((i <= mid ) && (j <= end )) {
		if (compare((char *)a + i * width, (char *)a + j * width) < 0)
			memcpy((char*)tmp + k++ * width, (char *)a + i++ * width, width);
		else
			memcpy((char*)tmp + k++ * width, (char *)a + j++ * width, width);
	}
		while (i <= mid)
			memcpy((char*)tmp + k++ * width, (char *)a + i++ * width, width);
		while (j <= end)
			memcpy((char*)tmp + k++ * width, (char *)a+ j++ * width, width);
	for (i = 0; i < k; i++) {
		memcpy((char*)a + (first + i) * width, (char *)tmp + i * width, width);
		
	}
}
void mergesort(void *a, int bottom, int top, int width, void* tmp, CMP compare)
{
	int mid;
	if (top > bottom) {
		mid = (bottom + top) / 2;
		mergesort(a, bottom, mid, width,  tmp, compare);
		mergesort(a, mid + 1, top, width, tmp, compare);
		mergeSortedNumber(a, bottom, mid, top, width, tmp, compare);
	}
}
int MergeSort(void* base, int num, int width, CMP cmp)
{
	void *tmp;
	if (!(tmp = malloc(num * width))) {
		printf("no memory!\n");
		return -1;
	}
	mergesort(base, 0, num - 1, width, tmp, cmp);
	return 0;
}
