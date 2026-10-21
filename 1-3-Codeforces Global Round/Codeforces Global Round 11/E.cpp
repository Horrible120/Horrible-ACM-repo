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
	ll x;
	cin>>x;
	vector<tuple<ll,char,ll>> ans;
	auto op=[&](ll a,char c,ll b){
		ans.emplace_back(a,c,b);
		return c=='+'?a+b:(a^b);
	};
	auto mul=[&](ll a,ll b){
		ll s=0;
		while(b){
			if(b&1){
				if(s) s=op(s,'+',a);
				else s=a;
			}
			b>>=1;
			if(b) a=op(a,'+',a);
		}
		return s;
	};

	ll p=1,y=x;
	while(p*2<=x){
		y=op(y,'+',y);
		p*=2;
	}
	y=op(x,'^',y);

	ll t=1;
	while((2*t*y+1)%x) t++;
	ll a=(2*t*y+1)/x,b=2*t;
	ll u=mul(x,a),v=mul(y,b);
	op(u,'^',v);

	cout<<ans.size()<<'\n';
	for(ll i=0;i<(ll)ans.size();i++){
		auto [a,c,b]=ans[i];
		cout<<a<<' '<<c<<' '<<b<<'\n';
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
