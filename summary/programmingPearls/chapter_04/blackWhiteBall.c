/*azhe 2013.11.6
 *Note: coffee opt issue
 *Usage: ./blackWhiteBall 10 20
 * arg1: numbers of black ball
 * arg2: numbers of white ball
 * */
#include <stdio.h>
#include <time.h>

enum COLOR{
	INIT = -1,
	BLACK,
	WHITE};
#if 0
void getTwoBeans(enum COLOR* b1, enum COLOR* b2)
{
	if (rand() % 2 == 1)
		*b1 = BLACK;
	else
		*b1 = WHITE;

	if (rand() % 2 == 1)
		*b2 = BLACK;
	else
		*b2 = WHITE;
}
#endif
int main(int argc, char ** argv)
{
	enum COLOR b1 = INIT, b2 = INIT;
	int n_b, n_w, t, n;
	int first, second;
	srand(time(NULL));
	if (argv[1] == NULL || argv[2] == NULL) {
		printf("arg1 and arg2 should not be null!\n");
		return -1;
	}
	/*黑白豆个数*/
	n_b = atoi(argv[1]);
	n_w = atoi(argv[2]);
	n = n_b + n_w;
	while (n > 1) {
		/*getTwoBeans(&b1, &b2);*/
		first = rand() % n;
		second = rand() % (n - 1);
		printf("b: %d, w: %d sum: %d\n", n_b, n_w, n);

		if (first < n_b && second < (n_b - 1)) { /*两者皆黑球*/
			n_b -= 2;
			n_b++;
			n--;
			printf("黑黑!\n");
		} else if (first >= n_b && second >= n_b){/*两者皆白球*/
			n_w -= 2;
			n_b++;
			n--;
			printf("白白!\n");
		} else { /*黑白各一个*/
			n_b--;
			n--;
			printf("黑白\n");
		}
	}
		if (n_b > n_w) {
			printf("余黑球\n");
		} else {
			printf("余白球\n");
		}

	return 1;
}
