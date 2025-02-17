#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

int l,la,lb;
char a[9000010];
char b[9000010];
int ans[9000010];

int main()
{
	
	gets(a);
	gets(b);
	
	la=strlen(a);
	lb=strlen(b);
	
	for(int i=0;i<la;i++)
		a[i]=a[i]-'0';
		
	for(int i=0;i<lb;i++)
		b[i]=b[i]-'0';
	
	l=max(la,lb);
	
	for(int i=0;i<l;i++)
	{
		ans[i]+=(a[i]+b[i])%10;
		ans[i+1]+=(a[i]+b[i])/10;
	}
	
	for(int i=0;i<l;i++)
		printf("%d",ans[i]);
	if(ans[l])
		printf("%d",ans[l]);
	
	return 0;
}
