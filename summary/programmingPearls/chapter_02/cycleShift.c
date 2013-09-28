/*Programing pearls:
 * azhe_liu 2013-09-27 田林十村
 * chapter 02: cycle shift
 * Note: read STDIN and cycle shift the input number
 * arg1: shift
 * Usage: cat sourcefile|./cycleShift 3
 * */
#include <stdio.h>
#include <string.h>
#include "baseLib.h"
#define MAX_LEN	1000
int main(int argc, char **argv)
{
	uint32 *a = malloc(sizeof(uint32) * MAX_LEN);
	uint32 input_nums;
	int shift, i;
	if (!argv[1]) {
		printf("arg1 must be shift\n");
		return -1;
	}
	shift = atoi(argv[1]);
	printf("shift:%d\n", shift);

	input_nums = readStdinNumToArray(a, sizeof(uint32) * MAX_LEN);
	for (i = 0; i < input_nums; i++)
		printf("a[%d]= %u", i, a[i]);
	return 0;
}
