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
	ll n;
	cin>>n;
	vector<array<ll,2>> pt(n+1);
	for(ll i=1;i<=n;i++)
		cin>>pt[i][0]>>pt[i][1];
	string s;
	cin>>s;

	vector<ll> ord(n+1);
	for(ll i=1;i<=n;i++)
		ord[i]=i;
	ll p=1;
	for(ll i=2;i<=n;i++)
		if(pt[i]<pt[p])
			p=i;
	swap(ord[1],ord[p]);

	auto cross=[&](ll u,ll v,ll w)->ll{
		return (pt[v][0]-pt[u][0])*(pt[w][1]-pt[u][1])
			-(pt[v][1]-pt[u][1])*(pt[w][0]-pt[u][0]);
	};

	for(ll i=1;i<=n-2;i++){
		ll nxt=i+1;
		for(ll j=i+2;j<=n;j++){
			ll val=cross(ord[i],ord[nxt],ord[j]);
			if((s[i-1]=='L'&&val<0) || (s[i-1]=='R'&&val>0))
				nxt=j;
		}
		swap(ord[i+1],ord[nxt]);
	}

	for(ll i=1;i<=n;i++)
		cout<<ord[i]<<" \n"[i==n];
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
