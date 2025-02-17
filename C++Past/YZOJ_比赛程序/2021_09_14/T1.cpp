#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;

int n[110],l;
int pr[3]={0,5,2};
int q;
int mid[1100];
int ans[1000];

int main()
{
	char c;
	c=getchar();
	while('0'<=c&&c<='9')
	{
		n[++l]=c-'0';
		c=getchar();
	}
	
	for(int i=1;i<=l/2;i++)
	{
		int x=n[i];
		n[i]=n[l-i+1];
		n[l-i+1]=x;
	}
	/*********************************************************/
	for(int i=1;i<=l;i++)
		for(int j=1;j<=l;j++)
			mid[i+j-1]+=n[i]*n[j];
	
	for(int i=1;i<=2*l-1;i++)
	{
		mid[i+1]+=mid[i]/10;
		mid[i]%=10;
	}
	
	if(mid[2*l])
		l=2*l;
	else
		l=2*l-1;
		
	for(int i=l;i>=1;i--)
	{
		ans[i]=mid[i]/4;
		mid[i-1]+=(mid[i]%4)*10;
	}
	
	if(!ans[l])
		l--;
	
	for(int i=l;i>=1;i--)
		printf("%d",ans[i]);
	
	return 0;
}
