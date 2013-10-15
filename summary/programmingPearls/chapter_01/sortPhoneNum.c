/*
*Usage: sortPhoneNum file
*Note: sort by using bit map 
*/

#include <stdio.h>
#include <string.h>
#define INFO_NUM	10000000
#define SIZE (INFO_NUM / 32 + 1)
#define BITS	32
#define SHIFT	5
#define MASK	0x1f
#define OLD
unsigned int phoneNumList[SIZE] = {0};
void setBit(int i, unsigned int* array){	array[i >> SHIFT] |= (1 << (i & MASK)); }
int testBit(int i, unsigned int *array){	return array[1 >> SHIFT] & (1 << (i & MASK)); }
int main(int argc, char** argv)
{
	FILE* fp;
	char * filename;
	char line[1024];
	int i, j, n, m, phoneNum;
	memset(line, 0, sizeof(line));
	if (argv[1] == NULL) {
		printf("arg1 must filename!\n");
		return -1;
	}

	filename = argv[1];
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("open file error\n");
		return -2;
	}
	
	while (1) {
		fgets(line, sizeof(line), fp);
		if (feof(fp)) break;
		//printf("%s, %d\n", line, atoi(line));
		//printf("%s", line);
		phoneNum = atoi(line);
#ifdef OLD
		n = phoneNum / BITS;
		m = phoneNum % BITS;
		phoneNumList[n] |= (1 << m);
#else
		setBit(phoneNum, phoneNumList);
#endif
		//printf("phoneNumList[%d] = %u, n = %d, m = %d\n", n, phoneNum_list[n], n, m);
	}
	fclose(fp);
#ifdef OLD
	for (i = 0; i < SIZE; i++) {
		if (phoneNumList[i] != 0) {
			for (j = 0; j < BITS; j++) {
				if (phoneNumList[i] & (1 << j))
					//printf("%d i = %d, j = %d\n", (i * BITS) + j, i, j);
					printf("%d\n", (i * BITS) + j);
			}
		}
	}
#else
	for (i = 0; i <= INFO_NUM; i++)
		if (testBit(i, phoneNumList))
			printf("%d\n", i);
#endif
	return 0;
}
