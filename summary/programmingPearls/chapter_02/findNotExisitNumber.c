/*azhe_liu 2013-9-24
 *Note: find a number that don't exit in a file
 *Usage: findNotExistNumber file maxNumber
 *file: input file
 *maxNumber: the max number in inputfile
 *
 * */

#include <stdio.h>
#include <string.h>
#include <baseLib.h>
typedef unsigned int uint32;

int test(uint32 num, int shift) {return num & (1 << shift);}

int clean_file(char* filename)
{
	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
}
#if 0
int FEN(FILE* fp_src, FILE* fp_left, FILE* fp_right, FILE* fp_tmp, int max_shift, uint32* result)
{
	uint32 num, i, j;

	char line[12];
	/*clean up file*/
	clean_file(fp_left);
	clean_file(fp_right);
	clean_file(fp_tmp);

	while (1) {
		fgets(line, sizeof(line), fp_src);
		if (feof(fp)) break;
		num = atoi(line);
	
		if (test(num, max_shift)) {
			fwrite(&num, sizeof(uint32), 1, fp_left);
			i++;
		} else {
			fwrite(&num, sizeof(uint32), 1, fp_right);
			j++;
		}
	}
	if (i <= j && i < (1 << (max_shift))) {
		FEN(fp_left, fp_right, fp_tmp, fp_left);
	} else if ()
}
#endif

int FNE(FILE *fp_src, char* file_left, char* file_right, char* file_tmp, int max_shift, uint32* result)
{
	char line[12];
	uint32 num, i, j;
	//clean_file(file_left);
	//clean_file(file_right);

	/*clean and write left*/
	if ((fp_l = fopen(file_left, "w")) == NULL) {
		printf("open %s failed!\n", file_left);
		return -1;
	}
	/*clean and write right*/
	if ((fp_r = fopen(file_right, "w")) == NULL) {
		printf("open %s failed!\n", file_right);
		goto open_file_right_failed;
	}

	while (1) {
		memset(line, 0, sizeof(line));
		fgets(line, sizeof(line), fp_src);
		if (feof(fp_src)) break;
		num = atoi(line);

		if (test(num, max_shift)) {
			fwrite(line, sizeof(line), 1, fp_l);
			i++;
		} else {
			fwrite(line, sizeof(line), 1, fp_r);
			j++;
		}
	}
	fclose(fp_r);
	fclose(fp_l);
	
	if (i == j && i == (1 << max_shift)) {
		goto cannot_find;
	}
	/*clean file temp*/
	clean_file(file_tmp);
	/*search in i*/
	if (i <= j)
		return FEN(file_left, file_right, file_tmp, file_left, max_shift - 1, &result);
	else
		return FEN(file_right, file_left, file_tmp, file_right, max_shift - 1, &result);
cannot_find:
	fclose(fp_r);
open_file_right_failed:
	fclose(fp_l);
	return -1;
}

int findNoExisitNumber(FILE *fp, uint32 max, uint32* result)
{
	int i = 0, max_shift;
	char cwd[MAXPATH];
	char file_l[MAXPATH], file_r[MAXPATH], file_t[MAXPATH],;
	FILE * fp_left, fp_right, fp_tmp;
	getpwd(cwd, MAXPATH);
	memset(file_l, 0, sizeof(file_l));
	memset(file_r, 0, sizeof(file_r));
	memset(file_t, 0, sizeof(file_t));

	/*file left*/
	snprintf(file_l, MAXPATH, "%s/left.%d", cwd, getpid());
	snprintf(file_r, MAXPATH, "%s/right.%d", cwd, getpid());
	snprintf(file_t, MAXPATH, "%s/tmp.%d", cwd, getpid());
	
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
	return 0;
}
