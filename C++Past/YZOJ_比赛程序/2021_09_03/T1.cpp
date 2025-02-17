#include<cstdio>
using namespace std;

struct Node
{
	float c,w;
}tool[1000010];

int T,n;

int main()
{
	scanf("%d",&T);
	
	for(int i=1;i<=T;i++)
	{
		int m=1,ans=0;
		
		scanf("%d",&n);
		for(int j=1;j<=n;j++)
			scanf("%f",&tool[i].w);
		for(int j=1;j<=n;j++)
			scanf("%f",&tool[i].c);
			
		/***********************************************************/
		
		for(int j=1;j<=n;j++)
			if(tool[j].c*tool[m].w<tool[j].w*tool[m].c)
				m=j;
		
		for(int j=1;j<=n;j++)
			if(tool[j].c*tool[m].w==tool[j].w*tool[m].c)
				ans++;
				
		if(tool[m].c/tool[m].w>=1000)
			printf("Impossible \n");
		else
			printf("%f.8 %d",tool[m].c/tool[m].w,ans);
		/***********************************************************/
		
		for(int j=1;j<-n;j++)
		{
			tool[i].w=0;
			tool[i].c=0;
		}
	}
	
	return 0;
}
