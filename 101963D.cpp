#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 998244353000, Mod = 998244353;

ll tt=1;
ll ask[301];

struct Eg{
	ll u,v,w;
	ll s,t;
	Eg(){}
	Eg(ll _u,ll _v,ll _w,ll _s,ll _t):u(_u),v(_v),w(_w),s(_s),t(_t){}
};

class H_sgm{
public:
	ll n,nd;
	v2ct<Eg> node;
	
	H_sgm(ll _sz,ll _nd){
		n=_sz;nd=_nd;
		node.assign(4*n+1,vector<Eg>());
	}
	
	void modify(ll u,ll l,ll r,Eg t){
		if(t.s>t.t||l>t.t||r<t.s) return;
		if(t.s>r||t.t<l) return;
		if(l>=t.s&&r<=t.t){
			node[u].emplace_back(t);
			return;
		}
		ll mid=l+r>>1;
		if(t.s<=mid)
			modify(u*2,l,mid,t);
		if(t.t>mid)
			modify(u*2+1,mid+1,r,t);
	}
	
	void sol(ll u,ll l,ll r,v2ct<ll>f){
		if(u==1){
			for(auto e:node[u])
				f[e.u][e.v]=f[e.v][e.u]=min(f[e.u][e.v],e.w);
			for(ll k=1;k<=nd;k++)
				for(ll i=1;i<=nd;i++)
					for(ll j=1;j<=nd;j++)
						f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
		}
		else
			for(auto e:node[u])
				for(ll i=1;i<=nd;i++)
					for(ll j=1;j<=nd;j++){
						f[i][j]=min(f[i][j],f[i][e.u]+e.w+f[e.v][j]);
						f[i][j]=min(f[i][j],f[i][e.v]+e.w+f[e.u][j]);
					}
		if(l==r){
			if(ask[l]){
				ll ans=0;
				for(ll i=1;i<=nd;i++)
					for(ll j=1;j<=nd;j++)
						ans=(ans+f[i][j])%Mod;
//				OOO
				cout<<ans<<endl;
			}
			return;
		}
		ll mid=l+r>>1;
		sol(u*2,l,mid,f);
		sol(u*2+1,mid+1,r,f);
	}
};

void solve(){
	ll n,m,q;
	cin>>n>>m>>q;
	vector<Eg> eg(1,Eg());
	for(ll i=1;i<=m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		eg.emplace_back(Eg(u,v,w,1,q));
	}
	for(ll i=1;i<=q;i++){
		ask[i]=0;
		ll op,x,y,w;
		cin>>op;
		if(op==1){
			cin>>x>>y>>w;
			eg.emplace_back(Eg(x,y,w,i,q));
		}
		if(op==2){
			cin>>x;
			eg[x].t=i-1;
		}
		if(op==3)
			ask[i]=1;
	}
	H_sgm sgm(q,n);
	for(ll i=1;i<eg.size();i++)
		sgm.modify(1,1,q,eg[i]);
	v2ct<ll> tmp(n+1,vector<ll>(n+1,INF));
	for(ll i=1;i<=n;i++)
		tmp[i][i]=0;
	sgm.sol(1,1,q,tmp);
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
