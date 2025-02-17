#include<cstdio>
#include<iostream>
using namespace std; 

int n,num[100086];

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
		
	for(int i=1;i<n;i++)
		for(int j=1;j<n;j++)
			if(num[j]>num[i])
				swap(num[i],num[j]);
				
	for(int i=1;i<=n;i++)
		printf("%d ",num[i]);
	
	return 0;
}
