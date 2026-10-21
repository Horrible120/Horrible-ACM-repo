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

void solve(){
	ll k;
	cin>>k;
	vector<ll> v(k+1);
	for(ll i=1;i<=k;i++){
		cin>>v[i];
		for(ll j=1;j<v[i];j++)
			cin>>v[0];
	}
	sort(v.begin()+1,v.end(),greater<ll>());
	ll ans=0;
	vector<ll> cnt(21,0);
	for(ll i=1;i<=k;i++){
		for(ll j=20;j>=0;j--){
			if(cnt[j]==0&&v[i]>=(1<<j)){
				cnt[j]=1;
				ans+=(1<<j);
				v[i]-=(1<<j);
			}
		}
	}
	cout<<ans<<endl;
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
