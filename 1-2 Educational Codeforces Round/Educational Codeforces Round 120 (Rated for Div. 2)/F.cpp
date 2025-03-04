#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>

using namespace std;

typedef long long ll;
typedef uint64_t ull;

mt19937_64 rnd(time(0));

ll tt;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	ull n;
	cin>>n;
	
	vector<ull> pr(n+1),f(n+1),pre(n+1),hs(n+1);
	map<ull,ull> mp;
	
	for(ull i=1;i<=n;i++)		//重要的素数预处理模块
		pr[i]=i;				//初始化pr
	
	for(ull i=2;i<=n;i++)
		if(pr[i]==i)
		{
			for(ull j=i;j<=n;j+=i)
				pr[j]=min(pr[j],i);
			hs[i]=rnd();
		}
	
	for(ull i=1;i<=n;i++)
	{
		ull x=i;
		
		if(pr[i]!=i)
			while(x!=1)
			{
				hs[i]^=hs[pr[x]];
				x/=pr[x];
			}
			
		pre[i]=pre[i-1]^hs[i];
		f[i]=f[i-1]^pre[i];
		mp[pre[i]]=i;
	}		
	
	//for(int i=1;i<=n;i++)
	//	cout<<pr[i]<<' ';
	//cout<<endl;
	
	if(f[n]==0)
	{
		cout<<n<<endl;
		for(int i=1;i<=n;i++)
			cout<<i<<' ';
		cout<<endl;
	}
	else if(mp[f[n]])
	{
		cout<<n-1<<endl;
		ull x=mp[f[n]];
		for(int i=1;i<=n;i++)
			if(i!=x)
				cout<<i<<' ';	
		cout<<endl;
	}
	else
	{
		ull flag=0,x1,x2;
		for(int i=1;i<=n;i++)
			if(mp[f[n]^pre[i]])
			{
				x1=i;
				x2=mp[f[n]^pre[i]];
				flag=1;
				break;
			}
		if(flag)
		{
			cout<<n-2<<endl;
			for(int i=1;i<=n;i++)
				if(i!=x1&&i!=x2)
					cout<<i<<' ';	
			cout<<endl;
		}
		else
		{
			cout<<n-3<<endl;
			for(int i=1;i<=n-1;i++)
				if(i!=2&&i!=n/2)
					cout<<i<<' ';	
			cout<<endl;
		}
	}
	
					
	
	return 0;
}


