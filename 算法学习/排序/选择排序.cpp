#include<cstdio>
#include<iostream>
using namespace std; 

int n,num[100086];

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
		
	int min;
		
	for(int i=1;i<n;i++)
	{
		min=i;
		for(int j=i+1;j<=n;j++)
			if(num[min]>num[j])
				min=j;
		swap(num[min],num[i]);
	}
	
	for(int i=1;i<=n;i++)
		printf("%d ",num[i]);
	
	return 0;
}
