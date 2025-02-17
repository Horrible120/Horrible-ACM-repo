#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int dp[25001];
/*
dp[i]=0 表示i面值的钱不能被凑出来
dp[i]=1 表示i面值的钱可以被凑出来
dp[i]=2 表示i面值的钱是货币系统中本来就有的钱
*/
int a[2001];//存钱的面值
int t,n,ans=0;
int main()
{
	freopen("money.in","r",stdin);
	freopen("money.out","w",stdout);
	scanf("%d ",&t);
	for(int i=1;i<=t;i++)
	{
		ans=0;//						重置 ans
		memset(dp,0,sizeof(dp));//		重置 dp[]
		memset(a,0,sizeof(a));//		重置 a[] 
		scanf("%d",&n);//				get  货币种数
		for (int j=1;j<=n;j++)
		{
			scanf("%d",&a[j]);//		get  货币系统 
			dp[a[j]]=2;//				把货币系统中的钱标好
		}
		sort(a+1,a+1+n);//				从小到大排序=>剪枝
		for (int j=1;j<=a[n];j++)//		凑钱 
		{
			if (dp[j]>0)//				如果dp[j]能被凑出来====\\ 
			{//												   ||
				for (int k=1;k<=n;k++)//					   ||	
				    if (j+a[k]<=a[n])//	防止数组越界           \/
					    dp[j+a[k]]=1;// 那么dp[j+a[k]]也能被凑出来
                    else break; //		如果越界=>结束 
			}
		}
		ans=n;
		for (int j=1;j<=n;j++)//		结算 
			if (dp[a[j]]==1) ans--;//		可以凑成=>删掉 
		printf("%d\n",ans);//			输出 
	}
