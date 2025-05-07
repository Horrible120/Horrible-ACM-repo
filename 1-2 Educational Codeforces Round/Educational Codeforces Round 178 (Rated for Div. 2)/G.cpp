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
	ll n,q;
	cin>>n>>q;
	
	ll cnt=0;
	vector<ll> g(n+1,0),ti(n+1,1),ki(q+1,0);
	v2ct<pll> tr(q*4+1);
	vector<ll> fa(n+1,0),siz(n+1,0),dis(n+1,0);
	vector<pair<ll&,ll>> bac;
	
	auto add_edge=[&](auto &&self,ll u,ll l,ll r,ll s,ll t,ll x,ll y)->void{
		if(l>=s&&r<=t){
			tr[u].emplace_back(x,y);
			return;
		}
		
		ll mid=l+r>>1;
		
		if(mid>=s)
			self(self,u*2,l,mid,s,t,x,y);
		if(mid+1<=t)
			self(self,u*2+1,mid+1,r,s,t,x,y);
	};
	
	auto get_fa_dis=[&](vector<ll> &fa,vector<ll> &dis,ll x)->pair<ll,ll>{
		ll res=0;
		while(fa[x]!=x){
			res+=dis[x];
			x=fa[x];
		}
		return make_pair(x,res);
	};
	
	auto dsu_merge=[&](vector<ll> &fa,vector<ll> &siz,vector<ll> &dis,vector<pair<ll&,ll>> &bac,ll &cnt,ll x,ll y)->void{

		auto [fx,dx]=get_fa_dis(fa,dis,x);
		auto [fy,dy]=get_fa_dis(fa,dis,y);
		
		if(fx==fy){
			if((dx+dy)&1){
				bac.emplace_back(cnt,cnt);
				cnt++;
			}
			return;
		}
		
		if(siz[fx]<siz[fy]){
			swap(fx,fy);
			swap(dx,dy);
		}
		
		bac.emplace_back(dis[fy],dis[fy]);
		dis[fy]=(1+dx+dy)&1;
		
		bac.emplace_back(siz[fx],siz[fx]);
		siz[fx]+=siz[fy];
		
		bac.emplace_back(fa[fy],fa[fy]);
		fa[fy]=fx;
	};
	
	for(ll i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=1;
		dis[i]=0;
	}
	
	for(ll i=1;i<=n;i++)
		cin>>g[i];
	
	for(ll i=1;i<=q;i++){
		ll x,y;
		cin>>x>>y>>ki[i];
		if(ti[x]+1<=i)
			add_edge(add_edge,1,1,q,ti[x],i-1,x,g[x]);
		g[x]=y;
		ti[x]=i;
	}
	
	for(ll i=1;i<=n;i++)
		add_edge(add_edge,1,1,q,ti[i],q,i,g[i]);
	
	auto DFS=[&](auto &&self,ll u,ll l,ll r)->void{
		ll mem=bac.size();
		for(auto [x,y]:tr[u])
			dsu_merge(fa,siz,dis,bac,cnt,x,y);
		
		ll mid=l+r>>1;
		if(l==r){
//			OOO
			if(ki[l]%3==0)
				cout<<0<<endl;
			else if(ki[l]%3==1)
				cout<<1<<endl;
			else
				cout<<(n-cnt)%2+1<<endl;
		}
		else{
			self(self,u*2,l,mid);
			self(self,u*2+1,mid+1,r);
		}
		
		while(bac.size()>mem){
			auto [it,val]=bac.back();
			bac.pop_back();
			it=val;
		}
	};
	
	DFS(DFS,1,1,q);
	
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
