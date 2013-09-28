#include <stdio.h>
#include "baseLib.h"

/*read STDIN number to array
 *return number of input
 * */
uint32 readStdinNumToArray(uint32* a, uint32 size)
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

