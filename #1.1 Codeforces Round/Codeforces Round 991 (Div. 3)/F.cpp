#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;
	
	while ( tt-- ) {
		ll n,q;
		cin>>n>>q;
		vector<ll> v(n+1),diff(n+1);
		vector<vector<ll>> Gcd(n+1,vector<ll>(22));
		for(ll i=1;i<=n;i++)
			cin>>v[i];
		for(ll i=1;i<n;i++)
			Gcd[i][0]=diff[i]=max(v[i+1]-v[i],v[i]-v[i+1]);
		for(ll i=1;i<=20;i++)
			for(ll j=1;j<n;j++)
				if(j+(1<<(i-1))<n) Gcd[j][i]=__gcd(Gcd[j][i-1],Gcd[j+(1<<(i-1))][i-1]);
				else Gcd[j][i]=Gcd[j][i-1];
		ll l,r;
//		OOO
		for(ll i=1;i<=q;i++){
			cin>>l>>r;
			if(l==r){
				cout<<0<<' ';
				continue;
			}
			r-=1;
			ll lg=(l==r)?0:__lg(r-l);
			cout<<__gcd(Gcd[l][lg],Gcd[r-(1<<lg)+1][lg])<<' ';
		}
		cout<<endl;
	}
	
	cout.flush();
	
	return 0;
}
