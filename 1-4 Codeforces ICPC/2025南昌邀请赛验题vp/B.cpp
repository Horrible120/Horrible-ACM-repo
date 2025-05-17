#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识

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

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,q,tot=0;
	cin>>n>>q;
	vector<ll> dep(n+1,0),dfn(n+1,0),siz(n+1,0),rnk(n+1,0);
	v2ct<ll> eg(n+1),fa(n+1,vector<ll>(22)),rgfa(n+1,vector<ll>(22));
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
	}
	
	auto DFS=[&](auto &&self,ll u)->void{
		dfn[u]=++tot;
		rnk[tot]=u;
		siz[u]=1;
		rgfa[u][0]=u;
		for(ll i=1;i<21;i++)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(auto v:eg[u]){
			if(v!=fa[u][0]){
				fa[v][0]=u;
				dep[v]=dep[u]+1;
				self(self,v);
				siz[u]+=siz[v];
			}
		}
	};
	
	fa[1][0]=1;
	DFS(DFS,1);
	
	auto glca=[&](ll u,ll v)->ll{
		if(dep[u]<dep[v])
			swap(u,v);
		
		ll c=0;
		while(dep[u]>dep[v]){
			while(((dep[u]-dep[v])>>c)&1)
				u=fa[u][c];
			c++;
		}
		
		if(u==v)
			return u;
		
		for(ll i=21;i>=0;i--){
			if(fa[u][i]!=fa[v][i])
				u=fa[u][i],
				v=fa[v][i];
		}
		return fa[u][0];
	};
	
	for(ll i=1;i<=21;i++)
		for(ll j=1;j<=n;j++)
			rgfa[j][i]=glca(rgfa[j][i-1],rgfa[min(n,j+(1<<(i-1)))][i-1]);
	OOO
	class Node{
	public:
		ll l,r,cnt;
		Node()=default;
	};
	
	ll cnt=0;
	vector<Node> tr(n<<6,Node());
	vector<ll> root(n+1,0);
	
	auto add_val=[&](auto &&self,ll &u,ll v,ll l,ll r,ll val)->void{
		if(!u)
			u=++cnt;
//		cout<<u<<' '<<v<<' '<<l<<' '<<r<<' '<<val<<endl;
		ll mid=l+r>>1;
		
		tr[u].cnt=tr[v].cnt+1;
		tr[u].l=tr[v].l;
		tr[u].r=tr[v].r;
		
		if(l==r)
			return;
		
		if(val<=mid){
			tr[u].l=0;
			self(self,tr[u].l,tr[v].l,l,mid,val);
		}
		else{
			tr[u].r=0;
			self(self,tr[u].r,tr[v].r,mid+1,r,val);
		}
	};
	
	for(ll i=1;i<=n;i++){
		add_val(add_val,root[i],root[i-1],1,n,rnk[i]);
		cout<<root[i]<<endl;
	}
		
	
	auto query=[&](auto &&self,ll u,ll v,ll l,ll r,ll s,ll t)->ll{
		if(l>=s&&r<=t)
			return tr[v].cnt-tr[u].cnt;
		
		ll mid=l+r>>1,res=0;
		if(mid>=s)
			res+=self(self,tr[u].l,tr[v].l,l,mid,s,t);
		if(mid+1<=t)
			res+=self(self,tr[u].r,tr[v].r,mid+1,r,s,t);
		return res;
	};
	
	auto kfa=[&](ll u,ll k)->ll{
		k-=1;
		ll c=0;
		while(k){
			if((k>>c)&1){
				u=fa[u][c];
				k-=(1<<c);
			}
			c++;
		}
		return u;
	};
	
	for(ll i=1;i<=n;i++)
		cout<<i<<' '<<dfn[i]<<' '<<siz[i]<<endl;
	
	while(q--){
		
		ll ql,qr,rt;
		cin>>ql>>qr>>rt;
		ll g=__lg(qr-ql+1);
		
		ll lc=glca(rgfa[ql][g],rgfa[qr-(1<<g)+1][g]);
		
		if(dfn[rt]<dfn[lc]||dfn[rt]>dfn[lc]+siz[lc]-1)
			cout<<lc<<endl;
		else{
			ll l=1,r=dep[rt];	// 1->他自己
			while(l<r){
				ll midd=l+r>>1;
//				cout<<l<<' '<<r<<endl;
				ll mid=kfa(rt,midd);
				cout<<"!!! "<<mid<<endl;
				if(query(query,root[dfn[mid]-1],root[dfn[mid]+siz[mid]-1],1,n,ql,qr))
					r=midd;
				else
					l=midd+1;
			}
			OOO
			cout<<lc<<' '<<l<<' '<<kfa(rt,l)<<endl;
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
