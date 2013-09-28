/*
*azhe_liu 2013-09-23
*libbase.so for programming pearls
*/

#ifdef DEBUG
    #define pr_debug(...) printf(...)
#else
    #define pr_debug(...)
#endif
typedef unsigned int uint32;
uint32 inputArray(uint32* a, uint32 size);

/*binary search using recursion*/
uint32 BinarySearch(uint32 * a, uint32 size, uint32 findNum, uint32* index);

void MergeSort(uint32* a, uint32 size);
