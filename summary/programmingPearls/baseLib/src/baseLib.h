/*
*azhe_liu 2013-09-23
*libbase.so for programming pearls
*/
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
    #define pr_debug(...) printf(...)
#else
    #define pr_debug(...)
#endif
typedef unsigned int uint32;

/*read num from STDIN to array*/
int readStdinNumToArray(int* a, int size);

/*binary search using recursion*/
uint32 BinarySearch(uint32 * a, uint32 size, uint32 findNum, uint32* index);
/*merge sort*/
typedef int (*CMP)(const void* a, const void* b);
int MergeSort(void* base, int num, int width, CMP cmp);
int randInt(int a, int b);
