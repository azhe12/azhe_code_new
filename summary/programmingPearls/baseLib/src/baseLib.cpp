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
#if 0
template<typename T>
void mergeSortedNumber(T * a, int first, int mid, int end, T *tmp)
{
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
		//pr_debug("%d\n", tmp[i]);
		
	}
	//pr_debug(">>>>\n");
}

template<typename T>
void mergesort(T *a, int bottom, int top, T* tmp)
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

/*merge sort
 *arg1: input array
 *arg2: array size
 *arg3: output sorted array
 * */
template<typename T>
void MergeSort(T * a, int size, T* b)
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
	mergesort(b, 0, size - 1, tmp);
	free(tmp);
}
#endif
