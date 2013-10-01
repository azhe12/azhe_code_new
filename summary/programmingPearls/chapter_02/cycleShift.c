/*Programing pearls:
 * azhe_liu 2013-09-27 田林十村
 * chapter 02: cycle shift
 * Note: read STDIN and cycle shift the input number
 * arg1: shift
 * Usage: cat sourcefile|./cycleShift 3
 * */
#define DEBUG
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "baseLib.h"
#define MAX_LEN	1000
int main(int argc, char **argv)
{
	uint32 *a = malloc(sizeof(uint32) * MAX_LEN);
	uint32 input_nums, t, left, right;
	int shift, i, k, start;
#if 1
	if (!argv[1]) {
		printf("arg1 must be shift\n");
		return -1;
	}
	shift = atoi(argv[1]);
	printf("shift:%d\n", shift);
#endif
	input_nums = readStdinNumToArray(a, sizeof(uint32) * MAX_LEN);
#if 0
	for (i = 0; i < input_nums; i++)
		printf("a[%d]= %u\n", i, a[i]);
#endif
	i = 0;
	start = 0;
	k = 0;
	while (k < input_nums) {
		if (i == 0)
			t = a[start];
		left = (start + i * shift) % input_nums;
		right = (left + shift) % input_nums;
		/*cycle shift*/
		if (right == start) {
			start++;
			i = 0;
			a[left] = t;
		} else {
			a[left] = a[right];
			i++;
		}
		printf("a[%u] = %u\n", left, a[left]);
		k++;
	}
	printf("*****\n");
	for (i = 0; i < input_nums; i++)
		printf("a[%d]= %u\n", i, a[i]);
	return 0;
}
