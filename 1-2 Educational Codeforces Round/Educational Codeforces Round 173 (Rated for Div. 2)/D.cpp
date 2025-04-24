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
	ll l,r,g,ansl,ansr;
	cin>>l>>r>>g;
	ll ans=-1;
	
	l=(l+g-1)/g;
	r=r/g;
	ansl=0,ansr=-1;
	
	for(ll i=l;i<=min(l+6,r);i++)
		for(ll j=r;j>=max(l,r-6);j--)
			if(j-i>ansr-ansl&&__gcd(j,i)==1)
				ansl=i,ansr=j;
	
	if(ansl==0){
		cout<<"-1 -1"<<endl;
	}
	else
		cout<<ansl*g<<' '<<ansr*g<<endl;
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
