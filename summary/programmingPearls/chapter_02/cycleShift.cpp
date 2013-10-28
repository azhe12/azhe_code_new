/*Programing pearls:
 * azhe_liu 2013-09-27 田林十村
 * chapter 02: cycle shift
 * Note: read STDIN and cycle shift the input number
 * arg1: shift
 * arg2: recurison algorithm
 * Usage: 1. cat sourcefile|./cycleShift 3
 *  2. ./cycleShift 10 -s <a.txt
 * */
#define DEBUG
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "baseLib.h"
#define MAX_LEN	1000
//using namespace std;
int n;
void swap(int *a, int first, int end, int shift)
{
	int i, t, size;
	for (i = 0; i < shift; i++) {
		t = a[first + i];
		a[first + i] = a[end - shift + i + 1];
		a[end - shift + i + 1] = t;
	}

}
void CFR(int *a, int first, int end, int shift)
{
	int left_width, right_width, len;
	len = end - first + 1;
	left_width = shift;
	right_width = len - shift;
	printf("first: %d, end: %d, shift: %d left: %d right %d\n", first, end, shift, left_width, right_width);
	if (left_width == right_width) {
		swap(a, first, end, shift);
		return;
	} else if (left_width < right_width) {
		swap(a, first, end, shift);
		CFR(a, first, first + right_width - 1, shift);
	} else {
		swap(a, first, end, len - shift);
		CFR(a, first + (len - shift), end, len - ((len -shift) * 2));
	}
}

void cycleShiftReplace(int *a, int input_nums, int shift)
{
	int first, mid, end;
	CFR(a, 0, input_nums - 1, shift);
}

void cycleShiftOrgin(int *a, int input_nums, int shift)
{
	int i, k, start, t, left, right;
	i = 0;
	start = 0;
	k = 0;
#if 1
	printf("*****\n");
	for (i = 0; i < n; i++)
		printf("a[%d]= %u\n", i, a[i]);
#endif
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
}

void reverse(int *a, int start, int end)
{
	int len = end - start + 1;
	int i, t;
	for (i = 0; i < len / 2; i++) {
		t = a[start + i];
		a[start + i] = a[end - i];
		a[end - i] = t;
	}
}
void cycleShiftReverse(int *a, int input_nums, int shift)
{
	reverse(a, 0, shift - 1);
	reverse(a, shift, input_nums - 1);
	reverse(a, 0, input_nums - 1);
}
int main(int argc, char **argv)
{
	int *a = (int*)malloc(sizeof(int) * MAX_LEN);
	int input_nums, i;
	int mode = 0;
	int shift;
#if 1
	if (!argv[1]) {
		printf("arg1 must be shift\n");
		return -1;
	}
	shift = atoi(argv[1]);
	if (argv[2]) {
		if (strcmp(argv[2], "-s") == 0)
			mode = 1;
		else if (strcmp(argv[2], "-r") == 0)
			mode = 2;
	}
	printf("shift:%d\n", shift);
#endif
	input_nums = readStdinNumToArray(a, sizeof(int) * MAX_LEN);
	if (shift >= input_nums) {
		printf("shift should be less than len of input number!\n");
		return -1;
	}
	switch (mode) {
	case 0:	
		cycleShiftOrgin(a, input_nums, shift);
		break;
	case 1:
		cycleShiftReplace(a, input_nums, shift);
		break;
	case 2:
		cycleShiftReverse(a, input_nums, shift);
		break;
	}
	
	printf("*****\n");
	for (i = 0; i < input_nums; i++)
		printf("a[%d]= %u\n", i, a[i]);
	return 0;
}
