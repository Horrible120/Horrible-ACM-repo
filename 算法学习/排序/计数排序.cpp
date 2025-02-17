#include<cstdio>
#include<iostream>
using namespace std; 

int n,num[100086];
int book[100086];
int sot[100086]; 

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
		
	for(int i=1;i<=n;i++)
		book[num[i]]++;
		
	for(int i=2;i<=100080;i++)
		book[i]+=book[i-1];
		
	for(int i=n;i>=1;i--)
		sot[book[num[i]]--]=num[i];
	
	for(int i=1;i<=n;i++)
		printf("%d ",sot[i]);
	
	return 0;
}
