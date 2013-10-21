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
typedef void (*SET)(void* a, void* b);

template<typename T>
//void mergeSortedNumber(T * a, int first, int mid, int end, T *tmp)
void mergeSortedNumber(T * a, int first, int mid, int end, \
		T *tmp, CMP compare, SET setValue)
{
	int i = first, j = mid + 1, k = 0;
	while ((i <= mid ) && (j <= end )) {
		if (compare(&a[i], &a[j]))
			setValue(&tmp[k++], &a[i++]);
			//tmp[k++] = a[i++];
		else
			setValue(&tmp[k++], &a[j++]);
			//tmp[k++] = a[j++];
	}
		while (i <= mid)
			setValue(&tmp[k++], &a[i++]);
			//tmp[k++] = a[i++];
		while (j <= end)
			setValue(&tmp[k++], &a[j++]);
			//tmp[k++] = a[j++];
	for (i = 0; i < k; i++) {
		setValue(&a[first + i], &tmp[i]);
		//a[first + i] = tmp[i];
		//pr_debug("%d\n", tmp[i]);
		
	}
	//pr_debug(">>>>\n");
}

template<typename T>
//void mergesort(T *a, int bottom, int top, T* tmp)
void mergesort(T *a, int bottom, int top, T* tmp, CMP compare, SET setValue)
{
	int mid;
	if (top > bottom) {
		mid = (bottom + top) / 2;
		mergesort(a, bottom, mid, tmp, compare, setValue);
		mergesort(a, mid + 1, top, tmp, compare, setValue);
		//mergeSortedNumber(a + bottom, mid - bottom + 1, a + mid + 1, top - mid, tmp);
		mergeSortedNumber(a, bottom, mid, top, tmp, compare, setValue);
	}
}

/*merge sort
 *arg1: input array
 *arg2: array size
 *arg3: output sorted array
 * */
template<typename T>
//void MergeSort(T * a, int size, T* b)
void MergeSort(T * a, int size, T* b, CMP compare, SET setValue)
{
	T * tmp;
	int i;
	if ( !(tmp = (T*)malloc(size * sizeof(T)))) {
		//printf("no memory!\n");
		cout<<"no memory!"<<endl;
		return;
	}
	for (i = 0; i < size; i++)
		setValue(&b[i], &a[i]);
		//b[i] = a[i];
	mergesort(b, 0, size - 1, tmp, compare, setValue);
	free(tmp);
}
#endif
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
			//setValue(tmp[k++], a[i++]);
			//setValue(tmp + k++, a + i++);
		else
			setValue(&tmp[k++], &a[j++]);
			//setValue(tmp[k++], a[j++]);
			//setValue(tmp + k++, a + j++);
	}
		while (i <= mid)
			setValue(&tmp[k++], &a[i++]);
			//setValue(tmp + k++, a + i++);
		while (j <= end)
			setValue(&tmp[k++], &a[j++]);
			//setValue(tmp + k++, a + j++);
	for (i = 0; i < k; i++) {
		setValue(&a[first + i], &tmp[i]);
		//setValue(a[first + i], tmp[i]);
		//setValue(a + first + i, tmp + i);
	}
}

template<typename T>
//void mergesort(T *a, int bottom, int top, T* tmp)
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

int compare(void *a, void *b)
{
	return *(int*)a <= *(int*)b;
}
void setValue(void* a, void *b)
{
	*(int*)a = *(int*)b;
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
	MergeSort(a, size, b, compare, setValue);
	for (i = 0; i < size; i++)
		printf("%d\n", b[i]);
	free(a);
}
