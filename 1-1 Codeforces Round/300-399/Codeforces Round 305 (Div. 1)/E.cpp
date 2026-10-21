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
class H_Fenwick{	//树状数组 类
public:
	ll n;	//总的元素个数
	vector<T> val;	//储存树状数组的数据
	
	H_Fenwick(ll _n):n(_n){	// n 个元素的初始化
		val.assign(n+1,0);
	}
	
	ll lb(ll x) {return x&-x;}	//求 lowbit
	
	T query_Prefsum(ll pos){	//求前缀和
		T res=0;
		while(pos){
			res+=val[pos];
			pos-=lb(pos);
		}
		return res;
	}
	
	T query_Rangesum(ll l,ll r){	//用前缀和求区间和
		return query_Prefsum(r)-query_Prefsum(l-1);
	}
	
	void val_add(ll pos,T key){	//单点修改: 加上key
		while(pos<=n){
			val[pos]+=key;
			pos+=lb(pos);
		}
	}
	
	void val_modify(ll pos,T key){
		val_add(pos,key-query_Rangesum(pos,pos));	//单点修改: 改为key
	}
};

void solve(){
	ll n,q,len=0;
	cin>>n>>q;
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
	vector<ll> dfn(tot+1),siz(tot+1,1);
	for(ll i=(ll)que.size()-1;i>=0;i--){
		ll u=que[i];
		siz[fail[u]]+=siz[u];
	}

	vector<ll> stk{0};
	ll tim=0;
	while(!stk.empty()){
		ll u=stk[stk.size()-1];
		stk.pop_back();
		dfn[u]=++tim;
		for(ll j=0;j<(ll)eg[u].size();j++)
			stk.emplace_back(eg[u][j]);
	}

	vector<vector<array<ll,3>>> qry(n+1);
	vector<ll> ans(q+1);
	for(ll i=1;i<=q;i++){
		ll l,r,k;
		cin>>l>>r>>k;
		qry[r].emplace_back(array<ll,3>{pos[k],i,1});
		qry[l-1].emplace_back(array<ll,3>{pos[k],i,-1});
	}

	H_Fenwick<ll> bit(tot+1);
	for(ll i=0;i<=n;i++){
		ll u=0;
		for(ll j=0;j<(ll)str[i].size();j++){
			u=son[u][str[i][j]-'a'];
			bit.val_add(dfn[u],1);
		}
		for(ll j=0;j<(ll)qry[i].size();j++){
			auto [v,id,sgn]=qry[i][j];
			ans[id]+=sgn*bit.query_Rangesum(dfn[v],dfn[v]+siz[v]-1);
		}
	}

	for(ll i=1;i<=q;i++)
		cout<<ans[i]<<'\n';
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
