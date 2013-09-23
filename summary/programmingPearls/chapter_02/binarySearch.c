#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#define uint32 unsigned int
typedef unsigned int uint32;
uint32 BinarySearch(uint32 * a, uint32 size, uint32 findNum, uint32* index)
{
	uint32 top, bottom, mid;
	bottom = 0;
	top = size - 1;
	while (1) {
		mid = (bottom + top) / 2;
		if (bottom == top) {
			if (findNum == a[bottom]) {/*find!*/
				*index = bottom;
				return 0;
			}
			else /*not find!*/
				return -1;
		} else if (bottom < top) {
			if (a[mid] > findNum)
				top = mid;
			else if (a[mid] < findNum)
				bottom = mid;
			else /*find!*/
				*index = bottom;
				return 0;
		}
	}
}
/*read STDIN number to array*/
uint32 inputArray(uint32* a, uint32 size)
{
	uint32 i = 0, num;
	while (scanf("%u", &num) != EOF) {
		if (i < size)
			a[i++] = num;
		else {
			printf("input exceed max length: %u\n", size);
			break;
		}
	}
	return i;
}
#define MAX_SIZE	10000000
int main(int argc, char** argv)
{
	uint32 t, result, input_size, i;
	/*input source number*/
	uint32 * a = malloc(sizeof(int) * MAX_SIZE);
	input_size = inputArray(a, MAX_SIZE);

	/*arg1 is number which want be searched*/
	if (!(argv[1])) {
		printf("arg1 must be not NULL!\n");
		return -2;
	}
	t = atoi(argv[1]);

	if (!BinarySearch(a, input_size, t, &i)) {
		printf("find: %u, index: %u\n", t, i);
	} else
		printf("not found!\n");



}
