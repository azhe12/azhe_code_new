/*azhe_liu 2013-9-24
 *Note: find a number that don't exit in a file
 *Usage: findNotExistNumber file maxNumber
 *file: input file
 *maxNumber: the max number in inputfile
 *
 * */

#include <stdio.h>

int findNoExisitNumber(FILE *fp, int max, int* result)
int main(int argc, char** argv)
{
	//int a[100] = {0, 1, 2, 3,4, 5, 7};
	int max, result;
	FILE* fp;
	char filepath[100];
	if (!argv[1] || !argv[2]) {
		printf("need two argument!\n");
		return -1;
	}
	if (!(fp = fopen(argv[1], "rw"))) {
		printf("can't open %s \n", argv[1]);
		return -2;
	}
	max = atoi(argv[2]);
	
	if (!findNoExisitNumber(fp, max, &result)) {
		printf("can't find not-exisit number!\n");
		fclose(fp);
		return -3;
	}
	fclose(fp);
}
