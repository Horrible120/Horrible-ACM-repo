#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
using namespace std;

int t;

mt19937_64 rnd(time(0));
uint64_t msk[100],dp[3][1<<20],f[2][100];
uint64_t prm[20]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,0};
uint64_t M=1e9+7;

void pre()
{
	for(int i=0;i<19;i++)
		msk[prm[i]]=1<<i;
	for(int i=1;i<=70;i++)
	{
		int num=i;
		for(int j=0;j<19;j++)
			if(i%prm[j]==0&&i!=prm[j])
				while(num>=prm[j]&&num%prm[j]==0)
				{
					msk[i]^=msk[prm[j]];
					num/=prm[j];
				}
					
	}
		
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	pre();
	
	int n;
	
	cin>>n;
	
	vector<int> v(n+1);
	for(int j=1;j<=70;j++)
			f[0][j]=1;
	
	for(int i=1;i<=n;i++)
	{
		cin>>v[i];
		f[0][v[i]]=f[1][v[i]]=(f[0][v[i]]+f[1][v[i]])%M;
	}
	
	dp[1][0]=1;
	for(int i=1;i<=70;i++)
	{
		//cout<<dp[i%2][0]<<endl;
		for(int j=0;j<(1<<19);j++)
		{
			dp[(i+1)%2][j^msk[i]]+=dp[i%2][j]*f[1][i];
			dp[(i+1)%2][j^msk[i]]%=M;
			dp[(i+1)%2][j]+=dp[i%2][j]*f[0][i];
			dp[(i+1)%2][j]%=M;
		}
		for(int j=0;j<(1<<19);j++)
			dp[i%2][j]=0;
	}
	
	cout<<(dp[1][0]-1+M)%M<<endl;
	
	return 0;
}
