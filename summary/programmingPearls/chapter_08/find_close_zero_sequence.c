/* chapter 8 习题8.10
 * azhe 2013.12.16
 * 求一个序列中的之和最接近0的子序列
 * usage: cat t.txt|./find_close_zero_sequence
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*read STDIN number to array*/
#define MAX_SIZE	10000000
struct node {
    int index;
    int sum;
};
int inputArray(int* a, int size)
{
	int i = 0, num;
	while (scanf("%d", &num) != EOF) {
		if (i < size)
			a[i++] = num;
		else {
			printf("input exceed max length: %d\n", size);
			break;
		}
	}
	return i;
}
int cmp(const void* a, const void* b)
{
    return (*(struct node *)a).sum - (*(struct node *)b).sum;
}
/*若一个子序列最接近0, 则包围其的两个累加和之差最小
 * 10 -1 3 -4 11
 * [2:3] 之和接近0. 则sum[1]和sum[4]之差最小
 * */
int find_close_zero_secquence(int *a, int len, int *start, \
                                int* end, int* sum)
{
    struct node* sumnode = malloc(sizeof(struct node) * len);
    int i, diff_sum, min_sum;
    if (sumnode == NULL) {
        printf("%s() no memory!\n", __func__);
        return -1;
    }
    memset(sumnode, 0, sizeof(struct node) * len);
    sumnode[0].index = 0;
    sumnode[0].sum = a[0];
    /*记录累加数组*/
    for (i = 1; i < len; i++) {
        sumnode[i].index = i;
        sumnode[i].sum = sumnode[i - 1].sum + a[i];
        printf("sum[%d]=%d\n", i, sumnode[i].sum);
    }
    /*对累加和进行排序， 相邻sum之差最小的，即为结果secquence*/
    qsort(sumnode, len, sizeof(sumnode[0]), cmp);
    /*设置min_sum初始值*/
    min_sum = sumnode[1].sum - sumnode[0].sum;
    if (sumnode[1].index > sumnode[0].index) {
        *start = sumnode[0].index + 1;
        *end = sumnode[1].index;
    } else {
        *start = sumnode[1].index + 1;
        *end = sumnode[0].index;
    }
    printf("---------------------\n");
    for (i = 1; i < len; i++) {
        printf ("sumnode[%d]=%d\n", i, sumnode[i].sum);
        diff_sum = sumnode[i].sum - sumnode[i - 1].sum;
        if (diff_sum < min_sum) {
            min_sum = diff_sum;
            if (sumnode[i].index > sumnode[i - 1].index) {
                *start = sumnode[i - 1].index + 1;
                *end = sumnode[i].index;
            } else {
                *start = sumnode[i].index + 1;
                *end = sumnode[i - 1].index;
            }
            printf("s: %d, e: %d\n", *start, *end);
        }
    }
    /*最接近0的sum*/
    *sum = min_sum;
    free(sumnode);
}
int main()
{
	int * a = malloc(sizeof(int) * MAX_SIZE);
    int start, end, max_sum;
    int input_size;
    if (a == NULL) {
        printf("no memory!\n");
        return -1;
    }
	input_size = inputArray(a, MAX_SIZE);
    find_close_zero_secquence(a, input_size, &start, &end, &max_sum);
    printf("close zero secquence is: [%d:%d] max_sum: %d\n", start, end, max_sum);
    free(a);
}
