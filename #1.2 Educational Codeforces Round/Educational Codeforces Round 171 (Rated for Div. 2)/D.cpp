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

long long n,q;
long long v[300010],pre[300010],ppre[300010],pppre[300010];

long long psum(long long x)
{
	return (n+(n+1-x))*x/2;
}

long long bs(long long x)
{
	long long l=1,r=n;
	while(l<r-1)
	{
		long long mid=(l+r)/2;
		if(psum(mid)<x)
			l=mid+1;
		else if(psum(mid-1)>=x)
			r=mid-1;
		else
			return mid;
	}
	if(x<=psum(l))
		return l;
	else
		return r;
}

long long sc(long long x)
{
	if(x==0)
		return 0;
	else
	{
		long long B=bs(x);
		long long ans=pppre[B-1];
		long long o=x-psum(B-1);
		ans+=ppre[B-1+o]-o*pre[B-1]-ppre[(B-1)];
		return ans;
	}
}

void ask(long long l,long long r)
{
	long long ans=sc(r)-sc(l-1);
	
	//cout<<">>";
	cout<<ans<<endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n;
	
	//for(int i=1;i<=n;i++)
	//{
	//	int m;
	//	cin>>m;
	//	cout<<bs(m)<<endl;
	//}
	
	for(int i=1;i<=n;i++)
		cin>>v[i];
	cin>>q;
	for(int i=1;i<=n;i++)
	{
		pre[i]=pre[i-1]+v[i];
		ppre[i]=ppre[i-1]+pre[i];
	}
	
	for(int i=1;i<=n;i++)
	{
		pppre[i]=pppre[i-1]+ppre[n]-ppre[i-1]-(n-i+1)*pre[i-1];
		//pppre[i]=pppre[i-1]+ppre[n]-(n-i+1)*pre[i-1]-pre[i-1];
	}
	
	long long l,r;	
	for(int i=1;i<=q;i++)
	{
		cin>>l>>r;
		ask(l,r);
	}

	return 0;
}

