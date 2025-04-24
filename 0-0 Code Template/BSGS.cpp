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

ll BSGS_Solve(ll a,ll b,ll p,ll ad){
	ll m=ceill(sqrtl(p));
	
	unordered_map<ll,pair<ll,ll>> mp;
	
	ll am=1;
	for(ll i=1;i<=m;i++)
		am=am*a%p;
	
	ll tmp=b;
	for(ll i=0;i<=m;i++){
		mp[tmp]=make_pair(1,i);
		tmp=tmp*a%p;
	}
	
	tmp=ad;
	for(ll i=1;i<=m;i++){
		tmp=tmp*am%p;
		if(mp[tmp].first)
			return i*m-mp[tmp].second;
	}
	return -1;
}

ll exBSGS(ll a,ll b,ll p){
	a%=p,b%=p;
	if(p==1||b==1) return 0;
	ll cnt=0,d=1,ad=1;
	while(1){
		d=__gcd(a,p);
		if(d==1) break;
		else if(b%d) return -1;
		cnt++;
		b/=d,p/=d;
		ad=ad*a/d%p;
		if(ad==b) return cnt;	//必须要加
	}
	ll res=BSGS_Solve(a,b,p,ad);
	if(res>=0)
		return res+cnt;
	return -1;
}

void solve(){
	ll a,p,b;
	while(cin>>a>>p>>b){
		if(a==0&&b==0&&p==0)
			return;
		ll ans=exBSGS(a,b,p);
		if(ans>=0)
			cout<<ans<<'\n';
		else
			cout<<"No Solution"<<'\n';
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
