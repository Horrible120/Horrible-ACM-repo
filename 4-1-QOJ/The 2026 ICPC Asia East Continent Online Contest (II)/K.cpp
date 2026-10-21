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
	vector<ll> a(n+1),c(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<=n) c[a[i]]++;
	}
	ll s=0;
	while(c[s]) s++;
	sort(a.begin()+1,a.end());
	vector<ll> b(1),num(1);
	for(ll i=1;i<=n;i++){
		if(b.size()==1||b[b.size()-1]!=a[i]){
			b.emplace_back(a[i]);
			num.emplace_back(1);
		}
		else num[num.size()-1]++;
	}
	ll m=b.size()-1;
	vector<ll> f(m+1);
	for(ll i=1;i<=m;i++){
		ll k=b[i]+s,x=s,p=i;
		while(x<n){
			ll y=k-x;
			while(p&&b[p]>y) p--;
			ll have=c[x];
			if(y!=x&&p&&b[p]==y) have+=num[p];
			ll need=1+(0<=y&&y<x);
			if(have<need) break;
			x++;
		}
		f[i]=x;
	}
	ll q,ans=0;
	cin>>q;
	while(q--){
		ll k;
		cin>>k;
		ll id=lower_bound(b.begin()+1,b.end(),k-s)-b.begin();
		if(id<=m&&b[id]==k-s) ans^=f[id];
		else ans^=s;
	}
	cout<<ans<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
