#include <stdio.h>
#include <arpa/inet.h>
#define X	3
#define Y	4
int main(int argc, char** argv)
{
	int a[X + 1][Y + 1];
	int i, j;
	memset(a, 0, sizeof(a));

	a[1][2] = 1;
	a[2][3] = 1;
	a[3][4] = 1;
	for (i = 1; i <= Y; i++) {
		printf("|   ");
		for (j = 1; j <= X; j++) {
			/*if (a[j][Y - i + 1] == 1)*/
			if (a[j][Y - i + 1] == 1)
				printf("*   ");
			else
				printf("    ");
		}
		printf("\n");
	}
	for (i = 1; i <= X + 1; i++)
		printf("----");
	printf("\n");
	return 0;
}
