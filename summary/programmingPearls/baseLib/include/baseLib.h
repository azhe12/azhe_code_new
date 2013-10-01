/*
*azhe_liu 2013-09-23
*libbase.so for programming pearls
*/
#ifndef _H_BASELIB
#ifdef DEBUG
#define pr_debug(fmt, args...) printf(fmt, args)
#else
#define pr_debug(fmt, args...)
#endif
typedef unsigned int uint32;
uint32 readStdinNumToArray(uint32* a, uint32 size);

/*binary search using recursion*/
uint32 BinarySearch(uint32 * a, uint32 size, uint32 findNum, uint32* index);

void MergeSort(uint32* a, uint32 size);

#endif /*_H_BASELIB*/
