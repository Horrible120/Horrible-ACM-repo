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
	ll s,k;
	cin>>s>>k;
	
//	OOO
	if(s%k==0){
		cout<<k<<endl;
		return;
	}
	else if(s>k*k){
		cout<<max(1ll,k-2)<<endl;
		return;
	}
	vector<ll> v(s+1,0);
	v[0]=1;
	for(ll i=k;i>=1;i--){
		if(k-i&1){
			for(ll j=0;j<=s;j++)
				v[j]=j+i<=s&&v[j+i];
			for(ll j=s-i;j>=0;j--)
				v[j]|=v[j+i];
		}
		else{
			for(ll j=s;j>=0;j--)
				v[j]=j-i>=0&&v[j-i];
			for(ll j=i;j<=s;j++)
				v[j]|=v[j-i];
		}
		if(v[s]){
			cout<<i<<endl;
			return;
		}
	}
	cout<<1<<endl;
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
