#include<cstdio>
#include<iostream>
using namespace std;
int n,m,g,gmax;
int x[9]={0,-1,0,1,1,1,0,-1,-1};
int y[9]={0,1,1,1,0,-1,-1,-1,0};
bool map[2000][2000];
int galaxy[2000][2000];
struct Dad
{
	int a;
	int b;
}dad[2000][2000];
Dad get_father(int a,int b)
{
	if(dad[a][b].a==a&&dad[a][b].b==b)
		return dad[a][b];
	else
		return dad[a][b]=get_father(dad[a][b].a,dad[a][b].b);
}
int main()
{
	int c,d=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%c",&c);
			if(c=='*')
			{
				map[i][j]=true;
				dad[i][j].a=i;
				dad[i][j].b=j;
			}	
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=8;k++)
				if(map[i+y[k]][j+x[k]])	
					dad[get_father(i+y[k],j+x[k]).a][get_father(i+y[k],j+x[k]).b]=dad[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j])
				galaxy[get_father(i,j).a][get_father(i,j).b]++;	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(galaxy[i][j])
			{
				gmax=max(gmax,galaxy[i][j]);
				g++;
			}
	printf("%d%d",g,gmax);		
	return 0;
}
