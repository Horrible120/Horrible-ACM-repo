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
	ll n,m,k;
	cin>>k>>n>>m;
	vector<ll> v(k+1,0),is(k+1,0);
	vector<tuple<ll,ll,ll>> st(k+1);
	v2ct<tuple<ll,ll,ll>> ad(k+1);
	vector<tuple<long double,ll,ll>> pd;
	for(ll i=1;i<=k;i++)
		cin>>v[i];
	for(ll i=1;i<=n;i++){
		ll op,u,x;
		cin>>op>>u>>x;
		if(op==1)
			st[u]=max(st[u],make_tuple(x,i,op));
		else if(op==2)
			ad[u].emplace_back(x,i,op);
		else
			pd.emplace_back(x,i,op);
	}
	
	for(ll i=1;i<=k;i++){
		auto [key,num,op]=st[i];
		if(num>0&&key>v[i])
			ad[i].emplace_back(key-v[i],num,op);
	}
	
	for(ll i=1;i<=k;i++){
		sort(ad[i].begin(),ad[i].end(),greater<tuple<ll,ll,ll>>());
		long double tmp=v[i];
		for(auto [key,num,op]:ad[i]){
			pd.emplace_back(make_tuple((tmp+key)/tmp,num,op));
			tmp+=key;
		}
	}
	
	sort(pd.begin(),pd.end(),greater<tuple<long double,ll,ll>>());
	
	vector<pll> ans;
	
	for(ll i=0;i<min(m,(ll)pd.size());i++){
		auto [key,num,op]=pd[i];
		ans.emplace_back(op,num);
	}
	
	sort(ans.begin(),ans.end());
	
	cout<<ans.size()<<endl;
	for(auto [op,num]:ans)
		cout<<num<<' ';
	cout<<endl;
	
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
