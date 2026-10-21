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
	string s;
	cin>>s;
	ll n=s.size(),m;
	cin>>m;
	vector<ll> p(n),vis(n),c;
	c.reserve(n);
	string ans(n,' ');

	while(m--){
		ll k,d;
		cin>>k>>d;
		ll pos=0,t=n-k+1;
		for(ll i=0;i<d;i++)
			for(ll j=i;j<k;j+=d) p[j]=pos++;
		for(ll i=k;i<n;i++) p[i]=i;
		for(ll i=0;i<n;i++){
			p[i]=(p[i]+n-1)%n;
			vis[i]=0;
		}

		for(ll i=0;i<n;i++){
			if(vis[i]) continue;
			c.clear();
			for(ll x=i;!vis[x];x=p[x]){
				vis[x]=1;
				c.emplace_back(x);
			}
			ll len=c.size(),step=t%len;
			for(ll j=0;j<len;j++)
				ans[(c[(j+step)%len]+t)%n]=s[c[j]];
		}
		s.swap(ans);
		cout<<s<<'\n';
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
