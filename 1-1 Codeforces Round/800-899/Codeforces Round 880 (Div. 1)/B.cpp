#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
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
	cin>>n>>m>>k;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	ll ans=0,cnt=0;
	
	sort(v.begin()+1,v.end());
	
	auto calc=[&](ll x)->void{
		ll p1=upper_bound(v.begin()+1,v.end(),x)-v.begin();
		ll p2=lower_bound(v.begin()+1,v.end(),x)-v.begin();
		ll ld,rd;
		
		if(p1<=k){
			ld=0;
		}else{
			ld=(v[p1-k]+1+x+1)/2;
		}
		
		if(p2+k-1>n){
			rd=m;
		}else{
			rd=(v[p2+k-1]-1+x)/2;
		}
		
		ll res=max(0ll,rd-ld+1);
		if(res>cnt){
			cnt=res;
			ans=x;
		}else if(res==cnt&&x<ans){
			ans=x;
		}
	};
	
	
	if(n<k){
		cout<<m+1<<' '<<0<<endl;
		return;
	}else{
		vector<ll> stk;
		for(ll i=1;i<=n;i++){
			stk.emplace_back(v[i]);
			if(v[i]>=1) stk.emplace_back(v[i]-1);
			if(v[i]>=2) stk.emplace_back(v[i]-2);
			if(v[i]+1<=m) stk.emplace_back(v[i]+1);
			if(v[i]+2<=m) stk.emplace_back(v[i]+2);
		}
		sort(stk.begin(),stk.end());
		stk.erase(unique(stk.begin(),stk.end()),stk.end());
		for(auto it:stk){
			calc(it);
		}
	}
	
//	OOO
	cout<<cnt<<' '<<ans<<endl;
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
