#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m;
	cin>>n>>m;
	v2ct<ll> v(n+1,vector<ll>(1,0));
	vector<ll> ti(n+1,0);
	vector<ll> hs(n+1,0);
	vector<ll> vis(m+1,0);
	
	map<pair<ll,ll>,ll> bk;
	
	for(ll i=1;i<=n;i++){
		ll x=rnd();
		hs[i]=x;
	}
	
	for(ll i=1;i<=n;i++){
		cin>>ti[i];
		v[i][0]=i;
		for(ll j=1;j<=ti[i];j++){
			ll x;
			cin>>x;
			v[i].emplace_back(x);
			bk[make_pair(i,x)]=1;
		}
	}
	
	auto cmp=[&](const vector<ll> &a,const vector<ll> &b){
		return (ll)a.size()>(ll)b.size();
	};
	
	sort(v.begin()+1,v.end(),cmp);
	
	for(ll i=1;i<=n;i++){
		for(ll j=2;j<=ti[v[i][0]];j++)
			if(vis[v[i][j]]!=vis[v[i][j-1]]){
				for(ll k=1;k<i;k++)
					if(bk[make_pair(v[k][0],v[i][j])]!=bk[make_pair(v[k][0],v[i][j-1])]){
						cout<<"YES\n"<<v[k][0]<<' '<<v[i][0]<<endl;
						return;
					}	
			}
				
//		OOO
		for(ll j=1;j<=ti[v[i][0]];j++)
			vis[v[i][j]]^=hs[v[i][0]];
	}
	cout<<"NO"<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
