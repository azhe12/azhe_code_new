/* chapter 8.1 find_max_sub_secquence
 * azhe 2013.12.11
 * 求一个序列中的最大子序列
 * usage: cat t.txt|./find_max_sub_secquence
 *
 * */
#include <stdio.h>
#include <stdlib.h>
/*read STDIN number to array*/
#define MAX_SIZE	10000000
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
int find_max_secquence(int *a, int len, int *start, int *end, int *max_sum)
{
    int i, j, max_i = 0, max_j = 0;
    int sum = 0, max = 0;
    for (i = 0; i < len; i++) {
        sum = 0;
        for (j = i; j < len; j++) {
            sum += a[j];
            if (sum > max) {
                max = sum;
                max_i = i;
                max_j = j;
            }
        }
    }
    *start = max_i;
    *end = max_j;
    *max_sum = max;
    return 0;
}
/* 
 *
 * */
void find_max_secquence_scan_algo(int *a, int len, int *start, int *end, int *max_sum)
{
    int i;
    int max_end_here = 0, max_so_far = 0;
    int seq_start = 0, max_start = 0, max_end = 0;
    for (i = 0; i < len; i++) {
        max_end_here += a[i];
        if (max_end_here < 0) {
            seq_start = i + 1;
            max_end_here = 0;
        }
        if (max_end_here > max_so_far) {
            max_so_far = max_end_here;
            max_start = seq_start;
            max_end = i;
        }
    }
   *start = max_start;
   *end = max_end;
   *max_sum = max_so_far;
}
int main()
{
	int * a = malloc(sizeof(int) * MAX_SIZE);
    int start, end, max_sum;
    int input_size;
	input_size = inputArray(a, MAX_SIZE);
    /*find_max_secquence(a, input_size, &start, &end, &max_sum);*/
    find_max_secquence_scan_algo(a, input_size, &start, &end, &max_sum);
    printf("max sub secquence is: [%d:%d] max_sum: %d\n", start, end, max_sum);
}
