/*azhe_liu 2013.10.24
 *Usage: ./bianWeiCi <word.txt
 *变位词统计
 * */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define WORDLEN		50
#define WORDMAX		100000

typedef int (*CMP)(const void* a, const void* b);
struct node {
	char word[WORDLEN];
	char sign[WORDLEN];
};
#if 1
int cmpChar(const void* a, const void* b)
{
	return *(char*)a - *(char*)b;
}
int cmpWord(const void* a, const void* b)
{
	if (strcmp(((struct node*)a)->sign, ((struct node*)b)->sign) > 0) {
		//printf("%s > %s\n", ((struct node*)a)->sign, ((struct node*)b)->sign);
		return 1;
	}
	else {
		//printf("%s <= %s\n", ((struct node*)a)->sign, ((struct node*)b)->sign);
		return -1;
	}
}
#endif
void mergeSortedNumber(void * a, int first, int mid, int end, int width, void *tmp, CMP compare)
{
	int i = first, j = mid + 1, k = 0;
	while ((i <= mid ) && (j <= end )) {
		if (compare((char *)a + i * width, (char *)a + j * width) < 0)
			memcpy((char*)tmp + (k++ * width), (char *)a + (i++ * width), width);
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
int main(int argc, char** argv)
{
	//char str[WORDLEN];
	struct node * word_list, *tmp;
	int i = 0, total, piece = 1;
	char prev[WORDLEN];
	int flag = 0;
	word_list = (struct node*)malloc(WORDMAX * sizeof(struct node));
	memset(word_list, 0, WORDMAX * sizeof(word_list[0]));
	memset(prev, 0, sizeof(prev));
	if (argv[1] != NULL) {
		if (strcmp(argv[1], "-q") == 0) {
			flag = 1;
			printf("use cLib qsort!\n");
		}
	}
	while (scanf("%s",(word_list + i)->word) != EOF) {
		strcpy((word_list + i)->sign, (word_list + i)->word);
		if (flag == 0)
			MergeSort((word_list + i)->sign, strlen((char*)((word_list + i)->sign)), sizeof((word_list)->sign[0]), cmpChar);
		else
			qsort((word_list + i)->sign, strlen((char*)((word_list + i)->sign)), sizeof((word_list)->sign[0]), cmpChar);
		i++;
	}
	total = i;

#if 0
	printf("word:\t sign:\n");
	for (i = 0; i < total; i++) {
		printf("%s \t %s\n", (word_list + i)->word, (word_list + i)->sign);
	}
#endif
	//qsort(word_list, total, sizeof(word_list[0]), cmpWord);
	if (flag == 0)
		MergeSort(word_list, total, sizeof(word_list[0]), cmpWord);
	else
		qsort(word_list, total, sizeof(word_list[0]), cmpWord);

/*print bian wei ci*/
	for (i = 0; i < total; i++) {
		if (strcmp(prev, word_list[i].sign) == 0) {
			printf(" %s", word_list[i].word);
		} else {
			printf("\n");
			printf("%s", word_list[i].word);
		}
		strcpy(prev, word_list[i].sign);
	}
	printf("\n");
	return 0;
}
