/*merge sort
 * azhe liu 2013.9.22
 * Read source file from STDIN
 * Output sorted data to STDOUT
 * Usage: cat sourcefile | ./mergeSort
 *
 * */
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "baseLib.h"
using namespace std;
#define ARRAY_SIZE	10000000

#if 0

typedef int (*CMP)(void* a, void* b);

template<typename T>
//void mergeSortedNumber(T * a, int first, int mid, int end, T *tmp)
void mergeSortedNumber(T * a, int first, int mid, int end, T *tmp, CMP compare)
{
	int i = first, j = mid + 1, k = 0;
	while ((i <= mid ) && (j <= end )) {
		//if (a[i] <= a[j])
		if (compare(&a[i], &a[j]))
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
		//pr_debug("%d\n", tmp[i]);
		
	}
	//pr_debug(">>>>\n");
}

template<typename T>
//void mergesort(T *a, int bottom, int top, T* tmp)
void mergesort(T *a, int bottom, int top, T* tmp, CMP compare)
{
	int mid;
	if (top > bottom) {
		mid = (bottom + top) / 2;
		mergesort(a, bottom, mid, tmp, compare);
		mergesort(a, mid + 1, top, tmp, compare);
		//mergeSortedNumber(a + bottom, mid - bottom + 1, a + mid + 1, top - mid, tmp);
		mergeSortedNumber(a, bottom, mid, top, tmp, compare);
	}
}

/*merge sort
 *arg1: input array
 *arg2: array size
 *arg3: output sorted array
 * */
template<typename T>
//void MergeSort(T * a, int size, T* b)
void MergeSort(T * a, int size, T* b, CMP compare)
{
	T * tmp;
	int i;
	if ( !(tmp = (T*)malloc(size * sizeof(T)))) {
		//printf("no memory!\n");
		cout<<"no memory!"<<endl;
		return;
	}
	for (i = 0; i < size; i++)
		b[i] = a[i];
	mergesort(b, 0, size - 1, tmp, compare);
	free(tmp);
}
#endif

int compare(void *a, void *b)
{
	return *(int*)a <= *(int*)b;
	//return *(int*)a >= *(int*)b;
}
int main(int argc, char** argv)
{
	int n, i = 0, size;
	int *a = (int*)malloc(sizeof(int) * ARRAY_SIZE);
	int *b;
	while(scanf("%d", &n) != EOF) {
		a[i++] = n;
		//pr_debug("input num = %d\n", a[i - 1]);
		cout<<"input num = "<<a[i - 1]<<endl;
	}
	size = i;
	b = (int*)malloc(sizeof(int) * size);
	/*merge sort*/
	MergeSort(a, size, b, compare);
	for (i = 0; i < size; i++)
		printf("%d\n", b[i]);
	free(a);
}
