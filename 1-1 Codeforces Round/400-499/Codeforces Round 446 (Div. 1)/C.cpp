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

class Edge{
public:
	ll u,v,w,idx;
	ll tu,tv;
	bool operator <(const Edge &a)const{
		return this->w<a.w;}
	Edge()=default;
	Edge(ll _u,ll _v,ll _w,ll _idx):u(_u),v(_v),w(_w),idx(_idx),tu(0),tv(0){}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	
	vector<Edge> eg(m+1);
	for(ll i=1;i<=m;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		eg[i]=Edge(u,v,w,i);
	}
	
	auto gf1=[&](vector<ll> &fa,ll &x)->ll{
		while(fa[x]!=x)
			x=fa[x];
		return x;
	};
	
	auto dsu_merge=[&](vector<ll> &fa,vector<ll> &siz,vector<pair<ll&,ll>> &bac,ll x,ll y)->void{
		ll fx=gf1(fa,x),fy=gf1(fa,y);
		if(fx==fy)
			return;
		if(siz[fx]<siz[fy])
			swap(fx,fy);
		
		bac.emplace_back(siz[fx],siz[fx]);
		siz[fx]+=siz[fy];
		bac.emplace_back(fa[fy],fa[fy]);
		fa[fy]=fx;
	};
	
	{	//Kruskal
		vector<ll> fa(n+1,0),siz(n+1,0);
		vector<pair<ll&,ll>> bac;
		
		for(ll i=1;i<=n;i++)
			fa[i]=i,
			siz[i]=1;
		
		sort(eg.begin()+1,eg.end());
		
		for(ll i=1;i<=m;i++){
			ll cur=i;
			while(cur<=m&&eg[cur].w==eg[i].w){
				eg[cur].tu=gf1(fa,eg[cur].u);
				eg[cur].tv=gf1(fa,eg[cur].v);
				cur++;
			}
			while(i<cur){
				dsu_merge(fa,siz,bac,eg[i].u,eg[i].v);
				i++;
			}
			i--;
		}
	}
	
	ll q;
	cin>>q;
	sort(eg.begin()+1,eg.end(),[](const Edge &a,const Edge &b){return a.idx<b.idx;});
	
	{
		vector<ll> fa(n+1,0),siz(n+1,0);
		vector<pair<ll&,ll>> bac;
		
		for(ll i=1;i<=n;i++)
			fa[i]=i,
			siz[i]=1;
		
		while(q--){
			ll k,flag=1;
			cin>>k;
			
			vector<Edge> egx(k+1);
			for(ll i=1;i<=k;i++){
				ll u;
				cin>>u;
				egx[i]=eg[u];
			}
			
			sort(egx.begin()+1,egx.end());
			
			for(ll i=1;i<=k;i++)
				if(gf1(fa,egx[i].tu)!=gf1(fa,egx[i].tv))
					dsu_merge(fa,siz,bac,egx[i].tu,egx[i].tv);
				else
					flag=0;
			
			for(ll i=1;i<=k;i++){
				fa[egx[i].tu]=egx[i].tu;
				siz[egx[i].tu]=1;
				fa[egx[i].tv]=egx[i].tv;
				siz[egx[i].tv]=1;
			}
			if(flag)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
		}
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
