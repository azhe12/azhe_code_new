#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "baseLib.h"
using namespace std;

#define WORD_LEN	50
#define	WORD_NUM	1000

#if 1

typedef int (*CMP)(void* a, void* b);
typedef void (*SET)(void* a, void* b);

template<typename T>
void mergeSortedNumber(T * a, int first, int mid, int end, \
		T *tmp, CMP compare, SET setValue)
{
	int i = first, j = mid + 1, k = 0;
	while ((i <= mid ) && (j <= end )) {
		if (compare(a[i], a[j]))
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

int compare(void *a, void* b)
{
	if ( strcmp((char*)a, (char*)b) <= 0) {
		printf("%s < %s\n", (char*)a, (char*)b);
		return 1;
	}
	else {
		printf("%s > %s\n", (char*)a, (char*)b);
		return 0;
	}
}
void setValue(void *a, void* b)
{
	//strcpy((char*)(*(char**)(a)), (char*)(*(char**)(b)));
	//strcpy((char*)((char *[WORD_LEN])a), (char*)((char *[WORD_LEN])b));
	//printf("setValue in\n");
	//printf("%s, %s\n", (char*)*((char (*)[WORD_LEN])a), (char*)*((char (*)[WORD_LEN])b));
	strcpy((char*)*((char (*)[WORD_LEN])a), (char*)*((char (*)[WORD_LEN])b));
	//printf("setValue out\n");
}

void printWord(char (*a)[WORD_NUM][WORD_LEN], int num)
{
	int i;
	for (i = 0; i < num; i++)
		printf("%s() %d: %s\n", __func__, i, *(a + i));
}

int main()
{
	char * str = "azhe";
	char * out;
	char in[20];
	int size;
	char (*input_str)[WORD_NUM][WORD_LEN];
	char (*output_str)[WORD_NUM][WORD_LEN];
	char *word;
	int word_num;
	int i = 0;

	input_str = (char (*)[WORD_NUM][WORD_LEN])malloc(WORD_LEN * WORD_NUM);
	output_str = (char (*)[WORD_NUM][WORD_LEN])malloc(WORD_LEN * WORD_NUM);
	word = (char*)malloc(WORD_LEN);

	memset(input_str, 0, WORD_LEN * WORD_NUM);
	memset(output_str, 0, WORD_LEN * WORD_NUM);
	memset(word, 0, WORD_LEN);
	while (scanf("%s", word) != EOF) {
		printf("input: %s\n", word);
		if (i >= WORD_NUM) {
			cout<<"only can process "<<WORD_NUM<<"words!"<<endl;
			break;
		}
		strcpy((char*)(*(input_str + i++)), word);
	}
	printf("----------------------------\n");
	word_num = i;

	MergeSort<char [WORD_NUM][WORD_LEN]>(input_str, word_num, output_str, compare, setValue);
#if 0	
	for (i = 0; i < word_num; i++) {
		setValue(output_str[i], input_str[i]);
	}
#endif
#if 0
	printWord(input_str, word_num);
#endif
	for (i = 0; i < word_num; i++)
		printf("%d: %s\n", i, (char*)(*(output_str + i)));
#if 0
	scanf("%s", in);
	size = strlen(str);
	out = (char*)malloc(size + 1);
	cout<<"str len = "<<strlen(str)<<endl;
	cout<<"in len = "<<strlen(in)<<endl;
	MergeSort(str, size, out);
	out[size] = '\0';
	printf("%s\n", out);
#endif
	free(input_str);
	free(output_str);
	return 0;
}
