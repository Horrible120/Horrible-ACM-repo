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
	vector<ll> pre(n+1);
	for(ll i=1;i<=n;i++){
		cin>>pre[i];
		pre[i]^=pre[i-1];
	}

	vector<ll> lm(n+1),rm(n+1),zl(n+1),zr(n+1);
	string ans(n,'0');

	for(ll len=n;len>=1;len--){
		for(ll l=1;l+len-1<=n;l++){
			ll r=l+len-1;
			ll val=pre[r]^pre[l-1];
			bool ok=(len==n)||zl[l]||zr[r]||(val&(lm[l]|rm[r]));
			if(!ok)
				continue;

			if(len==1)
				ans[l-1]='1';

			if(val==0)
				zl[l]=zr[r]=1;
			else{
				ll bit=1LL<<__lg(val);
				lm[l]|=bit;
				rm[r]|=bit;
			}
		}
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
