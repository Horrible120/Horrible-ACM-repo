#include<cstdio>
#include<iostream>
using namespace std; 

int n,num[100086];

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
		
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++)
			if(num[j]>num[i])
			{
				for(int k=i;k>j;k--)
					swap(num[k],num[k-1]);
				break;
			}
				
	
	for(int i=1;i<=n;i++)
		printf("%d ",num[i]);
	
	return 0;
}
