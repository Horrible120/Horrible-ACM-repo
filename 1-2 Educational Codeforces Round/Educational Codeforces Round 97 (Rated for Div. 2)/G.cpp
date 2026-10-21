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
	ll n,m,len=0;
	cin>>n>>m;
	vector<string> str(n+1);
	for(ll i=1;i<=n;i++){
		cin>>str[i];
		len+=str[i].size();
	}

	vector<array<ll,26>> son(len+1);
	vector<ll> fail(len+1),pos(n+1);
	ll tot=0;
	for(ll i=1;i<=n;i++){
		ll u=0;
		for(ll j=0;j<(ll)str[i].size();j++){
			ll c=str[i][j]-'a';
			if(!son[u][c])
				son[u][c]=++tot;
			u=son[u][c];
		}
		pos[i]=u;
	}

	vector<multiset<ll>> bag(tot+1);
	vector<ll> val(n+1),mx(tot+1,-1);
	for(ll i=1;i<=n;i++){
		bag[pos[i]].insert(0);
		mx[pos[i]]=0;
	}

	vector<ll> que;
	for(ll c=0;c<26;c++)
		if(son[0][c])
			que.emplace_back(son[0][c]);
	for(ll i=0;i<(ll)que.size();i++){
		ll u=que[i];
		for(ll c=0;c<26;c++){
			ll v=son[u][c];
			if(v){
				fail[v]=son[fail[u]][c];
				que.emplace_back(v);
			}else
				son[u][c]=son[fail[u]][c];
		}
	}

	vector<vector<ll>> eg(tot+1);
	for(ll u=1;u<=tot;u++)
		eg[fail[u]].emplace_back(u);
	vector<ll> siz(tot+1,1),hson(tot+1),top(tot+1),dfn(tot+1),rnk(tot+2);
	for(ll i=(ll)que.size()-1;i>=0;i--){
		ll u=que[i],fa=fail[u];
		siz[fa]+=siz[u];
		if(!hson[fa]||siz[u]>siz[hson[fa]])
			hson[fa]=u;
	}

	vector<ll> stk{0};
	ll tim=0;
	while(!stk.empty()){
		ll u=stk[stk.size()-1];
		stk.pop_back();
		dfn[u]=++tim;
		rnk[tim]=u;
		for(ll j=0;j<(ll)eg[u].size();j++){
			ll v=eg[u][j];
			if(v!=hson[u]){
				top[v]=v;
				stk.emplace_back(v);
			}
		}
		if(hson[u]){
			top[hson[u]]=top[u];
			stk.emplace_back(hson[u]);
		}
	}

	vector<ll> tr(4*(tot+1)+1,-1);
	auto build=[&](auto &&self,ll u,ll l,ll r)->void{
		if(l==r){
			tr[u]=mx[rnk[l]];
			return;
		}
		ll mid=(l+r)/2;
		self(self,u*2,l,mid);
		self(self,u*2+1,mid+1,r);
		tr[u]=max(tr[u*2],tr[u*2+1]);
	};
	auto modify=[&](auto &&self,ll u,ll l,ll r,ll loc,ll key)->void{
		if(l==r){
			tr[u]=key;
			return;
		}
		ll mid=(l+r)/2;
		if(loc<=mid)
			self(self,u*2,l,mid,loc,key);
		else
			self(self,u*2+1,mid+1,r,loc,key);
		tr[u]=max(tr[u*2],tr[u*2+1]);
	};
	auto query=[&](auto &&self,ll u,ll l,ll r,ll s,ll t)->ll{
		if(l>=s&&r<=t)
			return tr[u];
		ll mid=(l+r)/2,res=-1;
		if(mid>=s)
			res=max(res,self(self,u*2,l,mid,s,t));
		if(mid+1<=t)
			res=max(res,self(self,u*2+1,mid+1,r,s,t));
		return res;
	};
	auto path=[&](ll u)->ll{
		ll res=-1;
		while(u){
			res=max(res,query(query,1,1,tot+1,dfn[top[u]],dfn[u]));
			u=fail[top[u]];
		}
		return res;
	};
	build(build,1,1,tot+1);

	for(ll i=1;i<=m;i++){
		ll op;
		cin>>op;
		if(op==1){
			ll id,x;
			cin>>id>>x;
			ll u=pos[id];
			bag[u].erase(bag[u].find(val[id]));
			bag[u].insert(x);
			val[id]=x;
			mx[u]=*bag[u].rbegin();
			modify(modify,1,1,tot+1,dfn[u],mx[u]);
		}else{
			string q;
			cin>>q;
			ll u=0,ans=-1;
			for(ll j=0;j<(ll)q.size();j++){
				u=son[u][q[j]-'a'];
				ans=max(ans,path(u));
			}
			cout<<ans<<'\n';
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
//		cout.flush();
	}
	cout.flush();

	return 0;
}
