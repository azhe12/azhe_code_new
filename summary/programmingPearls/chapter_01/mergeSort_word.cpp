#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "baseLib.h"
using namespace std;

#define WORD_LEN	50
#define	WORD_NUM	1000

int compare(void *a, void* b)
{
	if ( strcmp((char*)*((char (*)[WORD_LEN])a), (char*)*((char (*)[WORD_LEN])b)) <= 0) {
		printf("%s < %s\n", (char*)*((char (*)[WORD_LEN])a), (char*)*((char (*)[WORD_LEN])b));
		return 1;
	}
	else {
		printf("%s > %s\n", (char*)*((char (*)[WORD_LEN])a), (char*)*((char (*)[WORD_LEN])b));
		return 0;
	}
}
void setValue(void *a, void* b)
{
	strcpy((char*)*((char (*)[WORD_LEN])a), (char*)*((char (*)[WORD_LEN])b));
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
	for (i = 0; i < word_num; i++)
		printf("%s\n", (char*)(*(output_str + i)));
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
