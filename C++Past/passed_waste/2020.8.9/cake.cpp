#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;

/****************************************************************/

struct cake
{
    int p,q,r;
}ca[310];

int n,t,ans;//					n为蛋糕种子数  t为天数  ans为最大美味值 
int f[310][20010];//			f[i][j]存 

/**************************************************************************/

bool cmp(cake a,cake b)//			sort排序优先级						
{
    if(a.q!=b.q) return a.q>b.q;//	先按成年期从大到小 
    return a.p<b.p;//				再按幼年期从小到大 
}

/*************************************************************************/

int main()/***愉***快***地***开***始***了***主***函***数***/
{
    //freopen("cake.in","r",stdin);
    //freopen("cake.out","w",stdout);
	scanf("%d%d",&n,&t);//								get n&t 
    for(int i=1;i<=n;i++)
     	scanf("%d%d%d",&ca[i].p,&ca[i].q,&ca[i].r);// 	get p&q&r 
    sort(ca+1,ca+n+1,cmp);//         					排序方便搜索 
    for(int i=1;i<=n;i++)//								01背包 
     	for(int j=t-ca[i].q;j>=1;j--)//					从保证成熟的那一天起 
      	{
	  		f[i][j]=f[i-1][j]; //						赋初值 
      		if(j>=ca[i].p)//							如果来得及种 
			    f[i][j]=max(f[i][j],f[i-1][j-ca[i].p]+ca[i].r); //取最大值 
		}
    for(int i=1;i<=t;i++)//								循环遍历 
     	ans=max(ans,f[n][i]);//							取最大值 
    printf("%d",ans);//									输出答案 
    return 0;
}/***愉***快***地***结***束***了***主***函***数***/
