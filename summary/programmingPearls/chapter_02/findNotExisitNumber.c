/*azhe_liu 2013-9-24
 *Note: find a number that don't exit in a file
 *Usage: findNotExistNumber file maxNumber
 *file: input file
 *maxNumber: the max number in inputfile
 *
 * */

#include <stdio.h>
typedef unsigned int uint32;

int test(uint32 num, int shift) {return num & (1 << shift);}
int FEN(FILE* fp_src, FILE* fp_left, FILE* fp_right, FILE* fp_tmp, int max_shift, uint32* result)
{
	uint32 num, i, j;

	char line[12];
	while (1) {
		fgets(line, sizeof(line), fp_src);
		if (feof(fp)) break;
		num = atoi(line);
	
		if (test(num, max_shift)) {
			
		}
	}
}

int findNoExisitNumber(FILE *fp, uint32 max, uint32* result)
{
	int i = 0, max_shift;
	char cwd[MAXPATH];
	char filename[MAXPATH];
	FILE * fp_left, fp_right, fp_tmp;
	getpwd(cwd, MAXPATH);
	/*file left*/
	snprintf(filename, MAXPATH, "%s/left.%d", cwd, getpid());
	if (! (fp_a = fopen(filename, "rw+"))) {
		printf("open %s failed!\n", filename);
		return -1;
	}
	memset(filename, 0, sizeof(filename));
	/*file right*/
	snprintf(filename, MAXPATH, "%s/right.%d", cwd, getpid());
	if (! (fp_right = fopen(filename, "rw+"))) {
		printf("open %s failed!\n", filename);
		return -1;
	}
	memset(filename, 0, sizeof(filename));
	/*file tmp*/
	snprintf(filename, MAXPATH, "%s/tmp.%d", cwd, getpid());
	if (! (fp_tmp = fopen(filename, "rw+"))) {
		printf("open %s failed!\n", filename);
		return -1;
	}
	memset(filename, 0, sizeof(filename));
	
	/*max_shift*/
	while (!(max & (1 << i))) i--;
	max_shift = i;
	
	if (FEN(fp, fp_left, fp_right, fp_tmp, max_shift, result))
		return 0;
	else
		return -1;
}
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
	if (!(fp = fopen(argv[1], "r"))) {
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
