#include<cstdio>
#include<cstring>
using namespace std;

int n;
int map[1010][1010];      //    x    o     .
int numb[1000100];
int numw[1000100];
int dad[1000100];
int xx[5]={0,1,0,-1,0};
int yy[5]={0,0,1,0,-1};
int Max,ans;

int find_d(int x)
{
	if(dad[x]==x)
		return x;
	else
		return dad[x]=find_d(dad[x]);
}

void link(int x,int y)
{
	int p=find_d(x);
	int q=find_d(y);
	
	dad[p]=q;
	
	numw[q]+=numw[p];
	numb[q]+=numb[p];
}

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%c",&map[i][j]);
			dad[i*n+j]=i*n+j;
			if(map[i][j]=='o')
				numw[i*n+j]++;
			else if(map[i][j]=='.')
				numb[i*n+j]++;
		}
			
			
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=4;k++)
				if(i+xx[k]<=n&&i+xx[k]>=1&&j+yy[k]<=n&&j+yy[k]>=1)
					if((map[i][j]=='o'||map[i][j]=='.')&&(map[i+xx[k]][j+yy[k]]=='o'||map[i+xx[k]][j+yy[k]]=='.'))
						if(find_d(i*n+j)!=find_d((i+xx[k])*n+j+yy[k]))
							link(i*n+j,(i+xx[k])*n+j+yy[k]);
		}
	
	for(int i=1;i<=n*n;i++)
		if(dad[i]=i)
			if(!numb[i])
				ans+=numw[i];
			else if(numb[i]==1&&numw[i]>Max)
				Max=numw[i];
	
	printf("%d",ans+Max);
	
	return 0;
}
