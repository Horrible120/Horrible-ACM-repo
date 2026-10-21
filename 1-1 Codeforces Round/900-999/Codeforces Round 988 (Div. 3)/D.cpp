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
		ll n,m,L;
		cin>>n>>m>>L;
		
		multiset<ll,greater<ll>> s,v;		//我澡称冯
		vector<ll> l(n+1),r(n+1),pw(m+1),coo(m+1);
		
		for(int i=1;i<=n;i++)
			cin>>l[i]>>r[i];
		for(int i=1;i<=m;i++)
			cin>>coo[i]>>pw[i];
		
		ll cur=1,power=1,ans=0,flag=1;
		for(int i=1;i<=n;i++){
			ll w=r[i]-l[i]+2;
			while(cur<=m&&coo[cur]<l[i]){
				v.insert(pw[cur++]);
			}
			while(power<w&&v.size()){
				power+=*v.begin();
				v.erase(v.begin());
				ans++;
			}
			if(power<w)
				flag=0;
		}
		if(flag)
			cout<<ans<<'\n';
		else
			cout<<-1<<'\n';
	}
	cout.flush();
	
	return 0;
}
