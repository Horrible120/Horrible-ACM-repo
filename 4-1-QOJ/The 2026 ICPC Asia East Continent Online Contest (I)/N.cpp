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

template<typename T>
class H_Fenwick{
public:
	ll n;
	v2ct<ll> pos;
	v2ct<T> val;

	H_Fenwick(ll _n,vector<ll>& x,vector<ll>& y):n(_n),pos(n+1),val(n+1){
		for(ll i=0;i<(ll)x.size();i++){
			for(ll j=x[i];j<=n;j+=lb(j)) pos[j].push_back(y[i]);
		}
		for(ll i=1;i<=n;i++){
			sort(pos[i].begin(),pos[i].end());
			pos[i].erase(unique(pos[i].begin(),pos[i].end()),pos[i].end());
			val[i].assign(pos[i].size()+1,INF);
		}
	}

	ll lb(ll x) {return x&-x;}

	T query_Prefmin(ll x,ll y){
		T res=INF;
		for(ll i=x;i;i-=lb(i)){
			ll p=upper_bound(pos[i].begin(),pos[i].end(),y)-pos[i].begin();
			for(ll j=p;j;j-=lb(j)) res=min(res,val[i][j]);
		}
		return res;
	}

	void val_min(ll x,ll y,T key){
		for(ll i=x;i<=n;i+=lb(i)){
			ll p=lower_bound(pos[i].begin(),pos[i].end(),y)-pos[i].begin()+1;
			for(ll j=p;j<(ll)val[i].size();j+=lb(j)) val[i][j]=min(val[i][j],key);
		}
	}
};

void solve(){
	ll n,mn=0,mx=0;
	cin>>n;
	vector<ll> x(n+1,0),y(n+1,0);
	for(ll i=1;i<=n;i++){
		ll r,a,b;
		cin>>r>>a>>b;
		x[i]=x[i-1]+r-a;
		y[i]=y[i-1]+r-b;
		mn=min(mn,x[i]);
		mx=max(mx,x[i]);
	}
	for(ll i=0;i<=n;i++) x[i]-=mn-1;

	H_Fenwick<ll> fwk(mx-mn+1,x,y);
	fwk.val_min(x[0],y[0],0);
	ll cur=0;
	for(ll i=1;i<=n;i++){
		ll best=fwk.query_Prefmin(x[i],y[i]);
		cur=min(cur+1,best);
		if(cur<best) fwk.val_min(x[i],y[i],cur);
	}
	cout<<n-cur<<'\n';
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
