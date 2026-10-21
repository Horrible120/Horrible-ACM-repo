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

struct Node{
	ll s[26]={},cnt=0;
};

void solve(){
	ll n,ans=0;
	cin>>n;
	vector<Node> tr(1);
	tr.reserve(500001);
	vector<ll> f(n+1,0);

	for(ll i=1;i<=n;i++){
		string s;
		cin>>s;
		ans+=i;	// 新增 f[i]=0 的贡献。
		ll u=0,d=0;
		for(char ch:s){
			ll x=ch-'a';
			if(!tr[u].s[x]){
				tr[u].s[x]=tr.size();
				tr.emplace_back();
			}
			u=tr[u].s[x];
			d++;
			ll c=++tr[u].cnt;
			// 计数从 c-1 变为 c，只需更新 f[c]。
			if(d>f[c]){
				ans-=(f[c]^c);
				f[c]=d;
				ans+=(f[c]^c);
			}
		}
		cout<<ans<<'\n';
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

//	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
