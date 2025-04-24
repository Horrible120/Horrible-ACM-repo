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
	ll n;
	cin>>n;
	v2ct<ll> v(21,vector<ll>());
	
	ll st=0;
	
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		if(x==-1)
			st=i;
		else
			v[x].emplace_back(i);
	}
	
	for(ll i=1;i<=20;i++)
		if(v[i].size())
			sort(v[i].begin(),v[i].end());
	
	vector<ll> ans(n+1,0);
	
//	for(ll i=1;i<=20;i++)
//		if(v[i].size()){
//			cout<<"!!! "<<i<<endl;
//			OOO
//			for(auto it:v[i])
//				cout<<it<<' ';
//			cout<<endl;
//		}
	
	ll l=0,r=0;
	for(ll i=20;i>=1;i--){
		if(v[i].size()){
			ll u=lower_bound(v[i].begin(),v[i].end(),st)-v[i].begin();
//			cout<<"!!! "<<i<<' '<<u<<endl;
			if(i&1){
				
				for(ll j=u;j<v[i].size();j++)
					ans[v[i][j]]=++r;
				for(ll j=u-1;j>=0;j--)
					ans[v[i][j]]=++r;
			}
			else{
				for(ll j=u;j<v[i].size();j++)
					ans[v[i][j]]=--l;
				
				for(ll j=u-1;j>=0;j--)
					ans[v[i][j]]=--l;
			}
		}
	}
	
	for(ll i=1;i<=n;i++)
		cout<<ans[i]-l+1<<' ';
	cout<<endl;
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
