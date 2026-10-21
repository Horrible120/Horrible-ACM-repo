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

	class Info{
	public:
		ll lhs,rhs,sum;
		Info():lhs(0),rhs(0),sum(0){}
	};

	ll cnt=0;
	vector<Info> tr((__lg(tot+1)+2)*len+1);
	vector<ll> rt(n+1);

	auto modify=[&](auto &&self,ll &u,ll pre,ll l,ll r,ll loc,ll key)->void{
		u=++cnt;
		tr[u]=tr[pre];
		if(l==r){
			tr[u].sum+=key;
			return;
		}
		ll mid=(l+r)/2;
		if(loc<=mid)
			self(self,tr[u].lhs,tr[pre].lhs,l,mid,loc,key);
		else
			self(self,tr[u].rhs,tr[pre].rhs,mid+1,r,loc,key);
		tr[u].sum=tr[tr[u].lhs].sum+tr[tr[u].rhs].sum;
	};

	auto query=[&](auto &&self,ll u,ll l,ll r,ll s,ll t)->ll{
		if(!u)
			return 0;
		if(l>=s&&r<=t)
			return tr[u].sum;
		ll mid=(l+r)/2,res=0;
		if(mid>=s)
			res+=self(self,tr[u].lhs,l,mid,s,t);
		if(mid+1<=t)
			res+=self(self,tr[u].rhs,mid+1,r,s,t);
		return res;
	};

	for(ll i=1;i<=n;i++){
		rt[i]=rt[i-1];
		ll u=0;
		for(ll j=0;j<(ll)str[i].size();j++){
			u=son[u][str[i][j]-'a'];
			modify(modify,rt[i],rt[i],1,tot+1,dfn[u],1);
		}
	}

	for(ll i=1;i<=q;i++){
		ll l,r,k;
		cin>>l>>r>>k;
		ll s=dfn[pos[k]],t=s+siz[pos[k]]-1;
		cout<<query(query,rt[r],1,tot+1,s,t)-query(query,rt[l-1],1,tot+1,s,t)<<'\n';
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
