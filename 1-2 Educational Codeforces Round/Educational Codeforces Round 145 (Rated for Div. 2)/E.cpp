#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

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
	ll a,b,n;
	cin>>n>>a>>b;
	
	vector<vector<ll>> ans(a+1,vector<ll>(b+1,0));
	vector<ll> v(n+1,0);
	
	ll cur=0,maxa=0,maxb=0;
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		cur+=v[i];
		maxb=max(cur,maxb);
		maxa=max(-cur,maxa);
	}
	
	auto calc=[&](ll va,ll vb)->ll{
		for(ll i=1;i<=n;i++){
			if(v[i]>0){
				ll tmp=min(min(v[i],va),b-vb);
				va-=tmp;
				vb+=tmp;
			}
			else{
				ll tmp=min(min(-v[i],vb),a-va);
				va+=tmp;
				vb-=tmp;
			}
		}
		return va;
	};
	
	for(ll i=0;i<=a+b;i++){
		ll ansa=-1,ansb=-1;
		for(ll va=max(0ll,i-b);va<=min(i,a);va++){
			ll vb=i-va;
			if(min(vb,a-va)<=maxa){
				if(ansa==-1){
					ansa=calc(va,vb);
				}
				ans[va][vb]=ansa;
			}
			else if(min(va,b-vb)<=maxb){
				if(ansb==-1){
					ansb=calc(va,vb);
				}
				ans[va][vb]=ansb;
			}
			else{
				ans[va][vb]=va-cur;
			}
		}
	}
	
	for(ll i=0;i<=a;i++)
		for(ll j=0;j<=b;j++)
			cout<<ans[i][j]<<" \n"[j==b];
	cout.flush();
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
