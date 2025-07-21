#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

class H_tree{
public:
	
	class Node {
	public:
		int to, w;  // to为边指向的节点，val为边权
		Node():to(0),w(0){}
		Node(ll _to,ll _w):to(_to),w(_w){}; 
	};
	
	ll n,dia;
	vector<ll> fa,d1,d2,dup,siz;	//父亲，向下最长路径，次长路径，向上最长路径，子树大小
	vector<ll> Center,Centro;	//中心，重心
	v2ct<Node> edge;	//邻接表
	
	H_tree(ll _n){
		n=_n;
		dia=0;
		fa.assign(n+1,0);
		edge.assign(n+1,vector<Node>());
		d1.assign(n+1,0);
		d2.assign(n+1,0);
		dup.assign(n+1,0);
		siz.assign(n+1,0);
	}
	
	void add_edge(ll u,ll v){
		edge[u].emplace_back(v,1);
		edge[v].emplace_back(u,1);
	}
	
	void add_W_edge(ll u,ll v,ll w){
		edge[u].emplace_back(v,w);
		edge[v].emplace_back(u,w);
	}
	
	void dfs_dia(ll u,ll _fa){
		fa[u]=_fa;
		for(auto &it:edge[u]){
			ll v=it.to,w=it.w;
			if(v==fa[u]) continue;
			dfs_dia(v,u);
			if(d1[v]+w>d1[u]){
				d2[u]=d1[u];
				d1[u]=d1[v]+w;
			}
			else if(d1[v]+w>d2[u])
				d2[u]=d1[v]+w;
		}
	}
	
	void dfs_up_dia(ll u,ll _fa){
		for(auto &it:edge[u]){
			ll v=it.to,w=it.w;
			if(v==fa[u]) continue;
			dup[v]=dup[u]+w;
			if(d1[v]+w!=d1[u])
				dup[v]=max(dup[v],d1[u]+w);
			else
				dup[v]=max(dup[v],d2[u]+w);
			dfs_up_dia(v,u);
		}
	}
	
	ll GetTreeDiameter(){
		dfs_dia(1,0);
		for(ll i=1;i<=n;i++)
			dia=max(dia,d1[i]+d2[i]);
		return dia;
	}
	
	vector<ll> GetTreeCenter() {  // 统计树的中心，记在Center内（若存在）
		dfs_dia(1, 0);
		dfs_up_dia(1, 0);
		Center.assign(1,0);
		for (int i = 1; i <= n; i++) {
			if (max(d1[i], dup[i]) < max(d1[Center[0]],dup[Center[0]]))	  // 找到了当前max(len1[x],up[x])最小点
				Center.assign(1,i);
			else if (max(d1[i], dup[i]) == max(d1[Center[0]],dup[Center[0]]))	  // 另一个中心
				Center.emplace_back(i);
		}
		return Center;
	}
	
	void GetTreeCentro(ll u,ll _fa) {  // 统计树的重心，记在Centro内（若存在）
		siz[u]=1;
		ll wei=0;
		fa[u]=_fa;
		for(auto &it:edge[u]){
			ll v=it.to;
			if(v==fa[u]) continue;
			GetTreeCentro(v,u);
			wei=max(wei,siz[v]);
			siz[u]+=siz[v];
		}
		wei=max(wei,n-siz[u]);
		if(wei<=n/2)
			Centro.emplace_back(u);
	}
};

ll ask(ll u,ll v){
	ll res;
	cout<<"? "<<u<<' '<<v<<endl;
	cin>>res;
	return res;
}

void ans(ll x){
	cout<<"! "<<x<<endl;
}

void solve(){
	ll n;
	cin>>n;
	H_tree tree(n);
	for(ll i=1;i<=n;i++){
		ll l,r;
		cin>>l>>r;
		if(l) tree.add_edge(i,l);
		if(r) tree.add_edge(i,r);
	}
	ll rt=1;
	auto cut=[&](ll u,ll v){
		tree.Centro=vector<ll>();
		tree.GetTreeCentro(u,0);
		for(ll i=0;i<tree.edge[u].size();i++)
			if(tree.edge[u][i].to==v){
//				cout<<"Cut"<<(*(tree.edge[u].begin()+i)).to<<endl;
				tree.edge[u].erase(tree.edge[u].begin()+i);
				break;
			}
		tree.n-=tree.siz[v];
	};
	
	while(tree.n>=1){
		if(tree.n==1){
			ans(rt);
			break;
		}
		tree.Centro=vector<ll>();
		tree.GetTreeCentro(rt,0);
		ll cto=tree.Centro[0];
		tree.GetTreeCentro(cto,0);
//		cout<<"!!!"<<cto<<endl;
		vector<H_tree::Node> &e=tree.edge[cto];
		if(e.size()==1){
			ll f=ask(cto,e[0].to);
			if(f) ans(e[0].to);
			else ans(cto);
			break;
		}
		else if(e.size()==2){
			ll x=e[0].to,y=e[1].to;
			ll f=ask(x,y);
			
			if(f==1){
				ans(cto);
				break;
			}
			else if(f==0)
				cut(x,cto),rt=x;
			else 
				cut(y,cto),rt=y;
		}
		else if(e.size()==3){
			ll x=e[0].to,y=e[1].to,z=e[2].to;
			if(tree.siz[z]>tree.siz[y])
				swap(y,z);
			else if(tree.siz[z]>tree.siz[x])
				swap(x,z);
			ll f=ask(x,y);
			
			if(f==1){
				cut(cto,x);
				cut(cto,y);
				rt=cto;
			}
			else if(f==0)
				cut(x,cto),rt=x;
			else 
				cut(y,cto),rt=y;
		}
	}
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
