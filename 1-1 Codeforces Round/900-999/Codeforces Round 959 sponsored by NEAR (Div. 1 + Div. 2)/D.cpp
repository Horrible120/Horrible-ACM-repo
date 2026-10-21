#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

class H_Dsu{
public:
	ll n;
	vector<ll> fa,siz;
	H_Dsu(ll _n):n(_n){
		fa.assign(n+1,0);
		for(ll i=1;i<=n;i++)
			fa[i]=i;
		siz.assign(n+1,1);
	}
	ll Fa(ll x){
		if(fa[x]==x) return x;
		else return fa[x]=Fa(fa[x]);
	}
	void merge(ll x,ll y){ //y向x合并
		ll fx=Fa(x),fy=Fa(y);
		if(fx==fy) return;
		siz[fx]+=siz[fy];
		fa[fy]=fx;
	}
};

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+1);
	vector<pair<ll,ll>> ans(n+1);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	H_Dsu dsu(n);
	
	for(ll i=n-1;i>=1;i--){
		vector<ll> tmp(n+1);
		for(ll j=1;j<=n;j++){
			if(tmp[v[j]%i]!=0){
				if(dsu.Fa(tmp[v[j]%i])!=dsu.Fa(j)){
					ans[i]=make_pair(tmp[v[j]%i],j);
					dsu.merge(tmp[v[j]%i],j);
					break;
				}
			}
			else
				tmp[v[j]%i]=j;
		}
	}
	cout<<"YES"<<endl;
	for(ll i=1;i<=n-1;i++)
		cout<<ans[i].first<<' '<<ans[i].second<<endl;
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
