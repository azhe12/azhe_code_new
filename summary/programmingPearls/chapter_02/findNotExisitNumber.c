/*azhe_liu 2013-9-24
 *Note: find a number that don't exit in a file
 *Usage: findNotExistNumber file maxNumber
 *file: input file
 *maxNumber: the max number in inputfile
 *
 * */

#include <stdio.h>
typedef unsigned int uint32;

int findNoExisitNumber(FILE *fp, int max, uint32* result)
{
	int i = 0, max_shift;
	char cwd[MAXPATH];
	char filename[MAXPATH];
	FILE * fp_a, fp_b, fp_c;
	getpwd(cwd, MAXPATH);
	/*file a*/
	snprintf(filename, MAXPATH, "%s/a.%d", cwd, getpid());
	if (! (fp_a = fopen(filename, "rw+"))) {
		printf("open %s failed!\n", filename);
		return -1;
	}
	memset(filename, 0, sizeof(filename));
	/*file b*/
	snprintf(filename, MAXPATH, "%s/b.%d", cwd, getpid());
	if (! (fp_b = fopen(filename, "rw+"))) {
		printf("open %s failed!\n", filename);
		return -1;
	}
	memset(filename, 0, sizeof(filename));
	/*file c*/
	snprintf(filename, MAXPATH, "%s/c.%d", cwd, getpid());
	if (! (fp_b = fopen(filename, "rw+"))) {
		printf("open %s failed!\n", filename);
		return -1;
	}
	memset(filename, 0, sizeof(filename));

	while (!(max & (1 << i))) i--;
	max_shift = i;
		
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
