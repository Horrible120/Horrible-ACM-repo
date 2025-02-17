#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int m,n,t;
float a[50010];
float stu[50010];
int top;

int main()
{
	scanf("%d",&m);
		
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&n,&t);
		
		for(int j=1;j<=n;j++)
			scanf("%f",&a[j]);
			
		if(t==3 || t==2)
			for(int j=1;j<=n;j++)
				a[j]=-a[j];
				
		if(t==2 || t==4)
			for(int j=1;j<=n;j++)
				a[j]-=1.00/j;
			
		top=1;
		stu[1]=a[1];
		
		for(int j=2;j<=n;j++)
			if(a[j]>stu[top])
				stu[++top]=a[j];
			else
				*lower_bound(stu+1,stu+top+1,a[j])=a[j];
					
		printf("%d\n",top);			
		
		for(int j=1;j<=n;j++)
		{
			a[j]=0;
			stu[j]=0;
		}	
	}
	return 0;
}
