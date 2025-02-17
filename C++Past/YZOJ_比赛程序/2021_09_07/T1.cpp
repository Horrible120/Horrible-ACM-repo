#include<cstdio>
using namespace std;

struct Rectangle
{
	int a,b,c,d;
	int t=0;
}rect[500010];

Rectangle start;
Rectangle end;

int n;
int ans=0;

int main()
{
	
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		scanf("%d%d%d%d",&rect[i].a,&rect[i].b,&rect[i].c,&rect[i].d);
	
	scanf("%d%d",&start.a,&start.b);
	scanf("%d%d",&end.a,&end.b);
	
	for(int i=1;i<=n;i++)
	{
		if(rect[i].a<start.a&&rect[i].b<start.b&&rect[i].c>start.a&&rect[i].d>start.b)
			rect[i].t++;
		
		if(rect[i].a<end.a&&rect[i].b<end.b&&rect[i].c>end.a&&rect[i].d>end.b)
			rect[i].t++;
			
		ans+=rect[i].t%2;
	}
	
	printf("%d",ans);
	
	return 0;
}
