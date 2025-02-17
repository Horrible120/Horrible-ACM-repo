#include<cstdio>
using namespace std;

char c[6];

int main()
{
	for(int i=1;i<=5;i++)
		scanf("%c",&c[i]);
	for(int i=5;i>=1;i--)
		printf("%c",c[i]);
	return 0;
}
