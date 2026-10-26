#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<ll> val(n+1),sum(n+1),ls(n+1),rs(n+1),stk;
	vector<vector<ll>> pos(k);
	pos[0].emplace_back(0);
	for(ll i=1;i<=n;i++){
		cin>>val[i];
		sum[i]=(sum[i-1]+val[i])%k;
		pos[sum[i]].emplace_back(i);
	}

	for(ll i=1;i<=n;i++){
		ll pre=0;
		while(!stk.empty()&&val[stk[stk.size()-1]]<val[i]){
			pre=stk[stk.size()-1];
			stk.pop_back();
		}
		ls[i]=pre;
		if(!stk.empty())
			rs[stk[stk.size()-1]]=i;
		stk.emplace_back(i);
	}
	auto query=[&](ll v,ll l,ll r)->ll{
		return upper_bound(pos[v].begin(),pos[v].end(),r)
			-lower_bound(pos[v].begin(),pos[v].end(),l);
	};

	ll ans=0;
	auto dfs=[&](this auto &&self,ll u,ll l,ll r)->void{
		while(u){
			if(u-l<=r-u){
				for(ll i=l;i<=u;i++)
					ans+=query((sum[i-1]+val[u])%k,u,r);
				ans--;
				self(ls[u],l,u-1);
				l=u+1;
				u=rs[u];
			}
			else{
				for(ll i=u;i<=r;i++)
					ans+=query((sum[i]-val[u]%k+k)%k,l-1,u-1);
				ans--;
				self(rs[u],u+1,r);
				r=u-1;
				u=ls[u];
			}
		}
	};
	dfs(stk[0],1,n);
	cout<<ans<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
