#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*#include <baseLib.h>*/

#define SIZE	(10 * (1 << 20)) /*10M*/
#define N		10
int main()
{
	int *data, *from, *to, top = 0;
	int i, t, x;
	data = malloc(SIZE * sizeof(*data));
	from = malloc(SIZE * sizeof(*from));
	to = malloc(SIZE * sizeof(*to));
	srand(time(0));
	
	for (i = 0; i < N; i++) { /*随机产生N个数，赋值data*/
		t = rand() % SIZE;
		data[t] = 1;
		from[t] = top;
		to[top] = t;
		top++;
		printf("fill %d\n", t);
	}
	
	printf("enter search number:\n");
	while (1) {
		scanf("%d", &x);
		/*判断x位置是否被初始化过*/
		if ((to[from[x]] == x) && from[x] < top) {
			printf("%d is exist!\n", x);
		} else {
			printf("%d is not exist!\n", x);
		}
	}
	return 1;
}
