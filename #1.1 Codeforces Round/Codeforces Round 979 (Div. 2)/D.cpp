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

ll tt;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		ll n,q,cnt=0;
		string s;
		cin>>n>>q;
		
		vector<ll> v(n+1),l(n+1),m(n+1); 
		
		for(int i=1;i<=n;i++)
			cin>>v[i];
		char c;
		for(int i=1;i<=n;i++)
		{
			cin>>c;
			if(c=='R')
				l[i]=1;
			else
				l[i]=0;
		}
		ll x;
		for(int i=1;i<=n;i++)
			m[i]=max(m[i-1],v[i]);
		for(int i=2;i<=n;i++)
			if(l[i]==1&&l[i-1]==0&&m[i-1]!=i-1)
				cnt++;
		for(int i=1;i<=q;i++)
		{
			cin>>x;
			if(l[x]==1&&l[x-1]==0&&m[x-1]!=x-1)
				cnt--;
			if(l[x+1]==1&&l[x]==0&&m[x]!=x)
				cnt--;
			l[x]^=1;
			if(l[x]==1&&l[x-1]==0&&m[x-1]!=x-1)
				cnt++;
			if(l[x+1]==1&&l[x]==0&&m[x]!=x)
				cnt++;
			if(cnt)
				cout<<"NO"<<endl;
			else
				cout<<"YES"<<endl;
		}
		
	}

	return 0;
}


