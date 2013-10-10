/*azhe_liu 2013-9-24
 *Note: find a number that don't exit in a file
 *Usage: findNotExistNumber file maxNumber
 *file: input file
 *maxNumber: the max number in inputfile
 *
 * */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <baseLib.h>

#define MAX_PATH	256
int test(int num, int shift) {return num & (1 << shift);}

int clean_file(char* filename)
{
	FILE* fp;
	fp = fopen(filename, "w");
	fclose(fp);
}

int read_first_num_from_file(char* filename)
{
	char line[12];
	FILE* fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("open %s failed!\n", filename);
		return -1;
	}
	memset(line, 0, sizeof(line));
	fgets(line, sizeof(line), fp);
	fclose(fp);
	return atoi(line);
}

int FNE(char* file_src, char* file_left, char* file_right, char* file_tmp, int max_shift, int* result)
{
	char line[12], num_char[11];
	int num = 0, i = 0, j = 0;
	FILE* fp_src, *fp_l, * fp_r;
	static int n = 0;

	/*clean left and right file*/
	clean_file(file_left);
	clean_file(file_right);

	printf("%s %s %s %s\n", file_src, file_left, file_right, file_tmp);
	/*open src file*/
	if ((fp_src = fopen(file_src, "r")) == NULL) {
		printf("open %s failed!\n", file_src);
		remove(file_left);
		remove(file_right);
		return -1;
	}
	/*open left*/
	if ((fp_l = fopen(file_left, "wa+")) == NULL) {
		printf("open %s failed!\n", file_left);
		goto open_file_left_failed;
	}
	/*open right*/
	if ((fp_r = fopen(file_right, "wa+")) == NULL) {
		printf("open %s failed!\n", file_right);
		goto open_file_right_failed;
	}

	while (1) {
		memset(line, 0, sizeof(line));
		memset(num_char, 0, sizeof(num_char));
		/*read  line*/
		fgets(line, sizeof(line), fp_src);
		if (feof(fp_src)) break;
		num = atoi(line);
		sprintf(num_char, "%u", num);
		num_char[10] = '\n';
		if (!test(num, max_shift)) {
			//fwrite(line, sizeof(line) - 2, 1, fp_l);
			fwrite(num_char, sizeof(num_char), 1, fp_l);
			i++;
		} else {
			//fwrite(line, sizeof(line) - 2, 1, fp_r);
			fwrite(num_char, sizeof(num_char), 1, fp_r);
			j++;
		}
	}
	
	if (i == j && i == (1 << max_shift)) {
		goto cannot_find;
	}

	/*close left right file*/
	fclose(fp_r);
	fclose(fp_l);
	fclose(fp_src);

	printf("i= %08u, j= %08u, max_shift= %d\n", i, j, max_shift);
	if (i == 0) {
		*result = read_first_num_from_file(file_right) - (1 << max_shift);
		remove(file_left);
		remove(file_right);
		remove(file_tmp);

		return 0;
	} else if (j == 0){
		*result = read_first_num_from_file(file_left) + (1 << max_shift);

		remove(file_left);
		remove(file_right);
		remove(file_tmp);
		return 0;
	}
	
	/*clean file temp*/
	//clean_file(file_tmp);
	/*search in i*/
	if (i <= j)
		return FNE(file_left, file_right, file_tmp, file_left, max_shift - 1, result);
	else
		return FNE(file_right, file_left, file_tmp, file_right, max_shift - 1, result);
cannot_find:
	fclose(fp_r);
	remove(file_right);
open_file_right_failed:
	fclose(fp_l);
	remove(file_left);
	remove(file_tmp);
open_file_left_failed:
	fclose(fp_src);
	return -1;
}

int findNoExisitNumber(char* file_src, int max, int* result)
{
	int i = 31, max_shift;
	char cwd[MAX_PATH];
	char file_l[MAX_PATH], file_r[MAX_PATH], file_t[MAX_PATH];
	FILE * fp_left, fp_right, fp_tmp;
	getcwd(cwd, MAX_PATH);
	memset(file_l, 0, sizeof(file_l));
	memset(file_r, 0, sizeof(file_r));
	memset(file_t, 0, sizeof(file_t));

	/*create left right temp file*/
	snprintf(file_l, MAX_PATH, "%s/left.%d", cwd, getpid());
	snprintf(file_r, MAX_PATH, "%s/right.%d", cwd, getpid());
	snprintf(file_t, MAX_PATH, "%s/tmp.%d", cwd, getpid());
	
	/*max_shift*/
	while (!(max & (1 << i))) i--;
	max_shift = i;
	
	if (FNE(file_src, file_l, file_r, file_t, max_shift, result))
		return 0;
	else
		return -1;
}

int main(int argc, char** argv)
{
	int max, result = 0;
	FILE* fp;
	char filepath[100];
	if (!argv[1] || !argv[2]) {
		printf("need two argument!\n");
		return -1;
	}
	max = atoi(argv[2]);

	if (!findNoExisitNumber(argv[1], max, &result)) {
		printf("can't find not-exisit number!\n");

		return -3;
	}
	printf("find %u\n", result);
	return 0;
}
