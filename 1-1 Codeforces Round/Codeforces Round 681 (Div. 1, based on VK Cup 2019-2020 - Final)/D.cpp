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

class H_sgm{
public:
	ll n,k;
	vector<vector<ll>> tr;
	
	H_sgm(ll _n,ll _k){
		n=_n;
		k=_k;
		tr.assign(4*n+6,vector<ll>(k+1,-1));
		for(ll i=1;i<=4*n+5;i++)
			tr[i][0]=0;
	}
	
	void solve(v2ct<ll> &dp,v2ct<ll> &v,vector<ll> &ti,ll u,ll l,ll r){
		
		if(l==r){
			dp[l]=tr[u];
			return;
		}
		
		ll mid=(l+r)>>1;
		
		tr[u*2]=tr[u];
		tr[u*2+1]=tr[u];
		
		for(ll i=l;i<=mid;i++){
			ll siz=min(ti[i],k);
			for(ll j=k-siz;j>=0;j--)
				if(tr[u*2+1][j]!=-1)
					tr[u*2+1][j+siz]=max(tr[u*2+1][j+siz],tr[u*2+1][j]+v[i][siz]);
		}
		
		for(ll i=mid+1;i<=r;i++){
			ll siz=min(ti[i],k);
			for(ll j=k-siz;j>=0;j--)
				if(tr[u*2][j]!=-1)
					tr[u*2][j+siz]=max(tr[u*2][j+siz],tr[u*2][j]+v[i][siz]);
		}
		
		solve(dp,v,ti,u*2,l,mid);
		solve(dp,v,ti,u*2+1,mid+1,r);
	}
	
};

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<vector<ll>> v(1,vector<ll>());
	v2ct<ll> dp(n+1,vector<ll>());
	vector<ll> ti(n+1,0);
	
	H_sgm sgm(n,k);
	
	for(ll i=1;i<=n;i++){
		cin>>ti[i];
		v.emplace_back(vector<ll>(ti[i]+2,0));
		for(ll j=1;j<=ti[i];j++)
			cin>>v[i][j],
			v[i][j]+=v[i][j-1];
	}
	
	sgm.solve(dp,v,ti,1,1,n);
	
//	cout<<endl;
//	for(ll i=1;i<=n;i++){
//		for(ll j=0;j<=ti[i];j++){
//			cout<<v[i][j]<<' ';
//		}
//		cout<<endl;
//	}
//	
//	cout<<endl;
//	for(ll i=1;i<=n;i++){
//		for(ll j=0;j<=min(ti[i],k);j++){
//			cout<<dp[i][j]<<' ';
//		}
//		cout<<endl;
//	}
//	
//	
//	
//	
	ll ans=0;
	for(ll i=1;i<=n;i++){
		for(ll j=0;j<=min(ti[i],k);j++)
			if(dp[i][k-j]!=-1)
				ans=max(ans,dp[i][k-j]+v[i][j]);
	}
	
//	OOO
	cout<<ans<<endl;
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
