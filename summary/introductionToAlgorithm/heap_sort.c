#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE    10000
#define LEFT(n) (2 * n)
#define RIGHT(n) (2 * n + 1)

/*#define DEBUG*/
#ifdef DEBUG
#define pr_debug(x...)  printf(x)
#else
#define pr_debug(x...)
#endif

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

static inline exchange(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}
#if 0
void max_heapify(int* a, int len, int i)
{
    int l, r, max;
    l = LEFT(i); 
    r = RIGHT(i);
    
    max = i;
    printf("l: %d a[l]: %d r: %d a[r]: %d\n", l, r, a[l], a[r]);
    if (l <= len && a[l] > a[max])
        max = l;
    if (r <= len && a[r] > a[max])
        max = r;
    
    if (max != i) {
        printf("max %d\n", max);
        exchange(&a[i], &a[max]);
        /*递归到叶子节点为止*/
        max_heapify(a, len, max);
    }
}
#endif
void max_heapify(int* a, int len, int i)
{
    int l, r, max, pos;
    pos = i + 1;
    l = LEFT(pos); 
    r = RIGHT(pos);
    
    max = pos;
    pr_debug("l: %d a[l]: %d r: %d a[r]: %d\n", l - 1, r - 1, a[l-1], a[r-1]);
    if (l <= len && a[l - 1] > a[max - 1])
        max = l;
    if (r <= len && a[r - 1] > a[max - 1])
        max = r;
    
    if (max != pos) {
        pr_debug("max %d\n", max - 1);
        exchange(&a[pos - 1], &a[max - 1]);
        /*递归到叶子节点为止*/
        max_heapify(a, len, max - 1);
    }
}
/*将无序数组转为最大堆*/
void build_max_heap(int *a, int len)
{
    int i;
    for (i = len / 2; i >= 1; i--) {
        max_heapify(a, len, i - 1);
    }
}
/*堆排序*/
void heap_sort(int* a, int len)
{
    int i;
    /*建立最大堆*/
    build_max_heap(a, len);
    for (i = len; i >= 2; i--) {
        /*交换根节点到最后*/
        exchange(&a[len - 1], &a[0]);
        len -= 1;
        /*当前根节点不符和最大堆性质，进行一次调整*/
        max_heapify(a, len, 0);
    }
}
int main()
{
    int *a = malloc(SIZE * sizeof(a[0]));
    int len, i;
    memset(a, 0, SIZE * sizeof(a[0]));
    len = readStdinNumToArray(a, SIZE);
    /*printf("len = %d\n", len);*/
    build_max_heap(a, len);
    /*max_heapify(a, len, 1);*/
    heap_sort(a, len);
    for (i = 0; i < len; i++) {
        printf("%d\n", a[i]);
    }
    return 0;
}
