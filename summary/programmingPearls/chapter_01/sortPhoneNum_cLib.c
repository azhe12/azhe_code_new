/*
*Usage: sortPhoneNum file
*Note: sort by using c lib
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INFO_NUM	10000000
#define SIZE (INFO_NUM / 32 + 1)
#define BITS 32

int cmp(const void *a, const void *b)
{
	return (*(int *)a) - (*(int*)b);
}
int main(int argc, char** argv)
{
	FILE* fp;
	char * filename;
	char line[1024];
	unsigned int * phoneNumList = malloc(INFO_NUM * sizeof(int));
	int phoneNum, i;
	int n = 0;
	memset(phoneNumList, 0, INFO_NUM * sizeof(int));
	memset(line, 0, sizeof(line));
#if 1
	if (argv[1] == NULL) {
		printf("arg1 must filename!\n");
		return -1;
	}
#endif
	filename = argv[1];
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("open file error\n");
		return -2;
	}
//read number from inputfile	
	while (1) {
		fgets(line, sizeof(line), fp);
		if (feof(fp)) break;
		phoneNum = atoi(line);
		//printf("phoneNum = %d\n", phoneNum);
		phoneNumList[n++] = phoneNum;
	}
	fclose(fp);
//sort
	qsort(phoneNumList, n, sizeof(int), cmp);

	for (i = 0; i < n; i++)
		printf("%d\n", phoneNumList[i]);
	return 0;
}
