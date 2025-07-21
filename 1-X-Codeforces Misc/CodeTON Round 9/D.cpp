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
#define OOO cout<<">>>>";	//调试标识

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;

	while ( tt-- ) {
		ll n,m;
		cin>>n>>m;
		vector<ll> v(m+1),ans(n+10);
		
		set<ll,greater<ll>> s;
		
		for(ll i=m;i>=1;i--)
			cin>>v[i],s.insert(v[i]);
		
		
		ans[1]=*s.begin();
		s.erase(s.begin());
		
		if(n>1&&s.empty()){
			cout<<-1<<endl;
			continue;
		}
		
		set<ll> k[n+1];
		
		for(ll i=1;i<=n;i++){
			for(ll j=1;j<=m&&(!ans[i]);j++)
				if(k[i].find(v[j])==k[i].end())
					ans[i]=v[j];
			for(ll j=2;i*j<=n;j++)
				k[i*j].insert(ans[i]);
			if(!ans[i]) break;
		}
		if(ans[n])
			for(ll i=1;i<=n;i++)
				cout<<ans[i]<<' ';
		else cout<<-1;
		cout<<endl;
	}
	
	cout.flush();
	
	return 0;
}
