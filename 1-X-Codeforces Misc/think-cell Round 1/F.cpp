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
	ll n,q,ans=0;
	cin>>n>>q;
	vector<ll> v(q+1,0);
	
	ll l=__lg(n)+1;
	ll ALL=(1<<l)-1;
		
	vector<ll> book1(ALL+1,0),book2(ALL+1,0);
	
	auto add1=[&](auto &&self,ll u)->void{
		if(book1[u]) return;
		book1[u]=1;
		if(book2[u]) ans=max(ans,u);
		for(ll i=0;i<l;i++)
			if(u>>i&1)
				self(self,u^(1<<i));
	};
	
	auto add2=[&](auto &&self,ll u)->void{
		if(book2[u]) return;
		book2[u]=1;
		if(book1[u]) ans=max(ans,u);
		for(ll i=0;i<l;i++)
			if(u>>i&1)
				self(self,u^(1<<i));
	};
	
	
	for(ll i=1;i<=q;i++){
		cin>>v[i];
		v[i]=(v[i]+ans)%n;
		
		add1(add1,v[i]);
		add2(add2,v[i]^ALL);
		cout<<ans<<" \n"[i==q];
		
		
	}
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
