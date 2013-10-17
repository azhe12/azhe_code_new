#include <iostream>
using namespace std;
template<typename T>
T max(T *a, T *b)
{
	return *a > *b ? *a : *b;
}
int main()
{
	int a = 2, b = 3;
	cout<<"hello world"<<endl;
	cout<<"max is "<<max(&a, &b)<<endl;
	return 0;
}
