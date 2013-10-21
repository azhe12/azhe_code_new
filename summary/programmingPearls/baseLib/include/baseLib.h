/*
*azhe_liu 2013-09-23
*libbase.so for programming pearls
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#ifdef DEBUG
    #define pr_debug(...) printf(...)
#else
    #define pr_debug(...)
#endif
typedef unsigned int uint32;

/*read num from STDIN to array*/
int readStdinNumToArray(int* a, int size);

/*binary search using recursion*/
uint32 BinarySearch(uint32 * a, uint32 size, uint32 findNum, uint32* index);
#if 1

typedef int (*CMP)(void* a, void* b);
typedef void (*SET)(void* a, void* b);

template<typename T>
void mergeSortedNumber(T * a, int first, int mid, int end, \
		T *tmp, CMP compare, SET setValue)
{
	int i = first, j = mid + 1, k = 0;
	while ((i <= mid ) && (j <= end )) {
		if (compare(&a[i], &a[j]))
			setValue(&tmp[k++], &a[i++]);
		else
			setValue(&tmp[k++], &a[j++]);
	}
		while (i <= mid)
			setValue(&tmp[k++], &a[i++]);
		while (j <= end)
			setValue(&tmp[k++], &a[j++]);
	for (i = 0; i < k; i++) {
		setValue(&a[first + i], &tmp[i]);
	}
}

template<typename T>
void mergesort(T *a, int bottom, int top, T* tmp, CMP compare, SET setValue)
{
	int mid;
	if (top > bottom) {
		mid = (bottom + top) / 2;
		mergesort(a, bottom, mid, tmp, compare, setValue);
		mergesort(a, mid + 1, top, tmp, compare, setValue);
		mergeSortedNumber(a, bottom, mid, top, tmp, compare, setValue);
	}
}

/*merge sort
 *arg1: input array
 *arg2: array size
 *arg3: output sorted array
 * */
template<typename T>
void MergeSort(T * a, int size, T* b, CMP compare, SET setValue)
{
	T * tmp;
	int i;
	if ( !(tmp = (T*)malloc(size * sizeof(T)))) {
		cout<<"no memory!"<<endl;
		return;
	}
	for (i = 0; i < size; i++) {
		setValue(&b[i], &a[i]);
		//setValue(*(b + i), *(a + i));
		//setValue(b + i, a + i);
	}
	mergesort(b, 0, size - 1, tmp, compare, setValue);
	free(tmp);
}
#endif
