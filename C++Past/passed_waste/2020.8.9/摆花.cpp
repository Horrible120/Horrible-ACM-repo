#include<cstdio>
#include<iostream>
using namespace std;
int n,m,a[110],ans;
int dfs[110][110];//   记忆化搜索库 
void DFS(int q,int p)//q为当前花种  p为剩余空间 
{
	if(p==0) ans=(ans+1)%1000007;//		如果摆满了ans++(取模) 
	else//                       		如果没摆满 
	{
		for(int i=q;i<=n;i++)//			只能摆编号大等于q的花 
			if(a[i])//                  如果还有库存 
			{
				a[i]--;//               库存减 1 
				DFS(i,p-1);//			往下搜(第i种花  p-1个空位) 
				a[i]++;//				回溯 
			}
	}
}
int main()/***愉***快***地***开***始***了***主***函***数***/
{
	freopen("flower.in","r",stdin);
	freopen("flower.out","w",stdout);
	scanf("%d%d",&n,&m);//				get  n&m 
	for(int i=1;i<=n;i++)				
		scanf("%d",&a[i]);//			get  a[] 
	DFS(1,m);//                         深搜 
	printf("%d",ans);//                 输出 
 } 
