#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "baseLib.h"

using namespace std;
/*read STDIN number to array
 *return number of input
 * */
int readStdinNumToArray(int* a, int size)
{
	int i = 0, num;
	while (scanf("%d", &num) != EOF) {
		if (i < size)
			a[i++] = num;
		else {
			printf("input exceed max length: %u\n", size);
			break;
		}
	}
	return i;
}

