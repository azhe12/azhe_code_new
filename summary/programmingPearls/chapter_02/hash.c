/* azhe 2013.10.31
 *Note: hash table include create, insert, search, delete
 *Option:
 * -c: create hash and write to name.dat(better for insert large number)
 * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN		6
#define ENCODE_WIDTH	3 /*utf-8*/

/*#define HASH_SIZE	200*/
#define HASH_SIZE		300
#define MAX_PATH		256
#define	MAX_FILENAME	512
#define	HASH_TABLE_FILE	"name.dat"
struct NAME{
	char name[NAME_LEN * ENCODE_WIDTH];
	int key;
	int c;
};
void initHash(struct NAME *h, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		memset(h[i].name, 0, sizeof(h[0].name));
		h[i].key = 0;
		h[i].c = 0;
	}
}

int hash(int x, int p)
{
	int k;
	k = x % p;
	return k;
}
#if 0
int solveConflictLine(int k)
{
	int i = 1;
	for 
}
#endif

int createHash(struct NAME *h, int size)
{
	int i = 0, j, k, sum, b = 0;
	int t = 0;
	char buf[NAME_LEN * ENCODE_WIDTH];
	int maxConflict = 0;
	while (scanf("%s", buf) != EOF) {
		/*printf("%d %s\n", t++, buf);*/
		/*strcpy(h[i].name, buf);*/
		for (j = 0; j < strlen(buf); j++) {
			sum += buf[j];
		}
		if (sum < 0) {
			/*printf("sum:old %d new:%d\n", sum, 0 - sum);*/
			sum = 0 - sum;
		}
		k = hash(sum, size);
		if (h[k].key == 0) { /*valid*/
			h[k].key = sum;
			strcpy(h[k].name, buf);
			h[k].c = 0;
		} else { /*conflict*/
			j = 1;
			k = (k + j * j) % size;
			while (h[k].key != 0) {
				j++;
#if 1
				if (b) {
				/*if (1) {*/
					k = (k + j * j) % size;
					b = 0;
				} else {
					k = (k - j * j) % size;
					/*printf("k=%d\n", k);*/
					if (k < 0)
						k = size + k;
					b = 1;
				}
#else
				k += j % size;
#endif
			}
			h[k].key = sum;
			strcpy(h[k].name, buf);
			h[k].c = j;
			printf("%d conflict , %d times\n", k, j);

			if (h[k].c > maxConflict)
				maxConflict = h[k].c;
		}
		/*printf("h[%d]\t%d\t%s\t%d\n", i, h[k].key, h[k].name, h[k].c);*/
	}
	printf("max conflict %d\n", maxConflict);
}

void printHash(struct NAME* h, int size)
{
	int i;
	printf("hash table\tkey\tname\tc\n");
	for (i = 0; i < size; i++) {
		printf("h[%d]\t%d\t%s\t%d\n", i, h[i].key, h[i].name, h[i].c);
	}
}
int main(int argc, char** argv)
{
	/*int *h;*/
	struct NAME *name_list;
	int size = HASH_SIZE, i;
	char path[MAX_PATH];
	char filename[];
	FILE* fp_ht;
	name_list = malloc(size * sizeof(struct NAME));
	/*memset(h, 0, HASH_SIZE * sizeof(struct NAME));*/
	if (argv[1] == NULL) {
		printf("arg1 should not be null!\n");
		return -1;
	}
	/*init and create hash table*/
	if (strcmp(argv[1], "-c") == 0) {
		initHash(name_list, size);
		createHash(name_list, size);
	
	/*write hash table to file ht.dat*/
	getcwd(path, sizeof(path));
	sprintf(filename, "%s/%s", path, HASH_TABLE_FILE);
	
	if ((fp = fopen(filename, "ab+")) == NULL) {
		printf("open %s failed\n", filename);
		return -1;
	}
	for (i = 0; i < size; i++) {
		fwrite(name_list[i], sizeof(struct NAME), 1, fp_ht);
	}

	fclose(fp_ht);
	}
	/*printf("path: %d");*/
	/*printHash(name_list, size);*/
	/*createHash*/
	return 0;
}
