#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE    10000
#define LEFT(n) (2 * n)
#define RIGHT(n) (2 * n + 1)
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
        max_heapify(a, len, max);
    }
}
int main()
{
    int *a = malloc(SIZE * sizeof(a[0]));
    int len, i;
    memset(a, 0, SIZE * sizeof(a[0]));
    len = readStdinNumToArray(a, SIZE);
    printf("len = %d\n", len);
    max_heapify(a, len, 2);
    for (i = 0; i < len; i++) {
        printf("%d\n", a[i]);
    }
    return 0;
}
