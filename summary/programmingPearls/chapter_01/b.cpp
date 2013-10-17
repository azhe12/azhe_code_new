#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "baseLib.h"
using namespace std;

int main()
{
	char * str = "azhe";
	char * out;
	char in[20];
	int size;
	scanf("%s", in);

	size = strlen(str);
	out = (char*)malloc(size + 1);
	cout<<"str len = "<<strlen(str)<<endl;
	cout<<"in len = "<<strlen(in)<<endl;
	MergeSort(str, size, out);
	out[size] = '\0';
	printf("%s\n", out);
}
