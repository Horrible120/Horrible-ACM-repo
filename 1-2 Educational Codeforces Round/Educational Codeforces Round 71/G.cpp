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
	ll n;
	cin>>n;
	vector<vector<ll>> eg(n+1);
	vector<ll> fa(n+1),val(n+1),cur(n+1);
	for(ll i=1;i<=n;i++){
		ll op;
		char c;
		cin>>op;
		if(op==2)
			cin>>fa[i];
		cin>>c;
		val[i]=c-'a';
		eg[fa[i]].emplace_back(i);
	}

	ll m;
	cin>>m;
	vector<array<ll,26>> nxt(2);
	nxt.reserve(400002);
	vector<vector<pair<ll,ll>>> ask(n+1);
	vector<ll> ans(m);
	for(ll i=0;i<m;i++){
		ll u,p=1;
		string s;
		cin>>u>>s;
		for(ll j=0;j<(ll)s.size();j++){
			ll c=s[j]-'a';
			if(!nxt[p][c]){
				ll v=nxt.size();
				nxt.emplace_back(array<ll,26>{});
				nxt[p][c]=v;
			}
			p=nxt[p][c];
		}
		ask[u].emplace_back(p,i);
	}

	ll cnt=(ll)nxt.size()-1;
	vector<ll> fail(cnt+1);
	vector<vector<ll>> son(cnt+1);
	queue<ll> que;
	for(ll c=0;c<26;c++){
		ll v=nxt[1][c];
		if(v){
			fail[v]=1;
			que.emplace(v);
		}
		else
			nxt[1][c]=1;
	}
	while(!que.empty()){
		ll u=que.front();
		que.pop();
		son[fail[u]].emplace_back(u);
		for(ll c=0;c<26;c++){
			ll v=nxt[u][c];
			if(v){
				fail[v]=nxt[fail[u]][c];
				que.emplace(v);
			}
			else
				nxt[u][c]=nxt[fail[u]][c];
		}
	}

	vector<ll> dfn(cnt+1),out(cnt+1),bit(cnt+1);
	ll tim=0;
	stack<ll> stk;
	stk.emplace(1);
	while(!stk.empty()){
		ll u=stk.top();
		stk.pop();
		if(u<0){
			out[-u]=tim;
			continue;
		}
		dfn[u]=++tim;
		stk.emplace(-u);
		for(ll i=(ll)son[u].size()-1;i>=0;i--)
			stk.emplace(son[u][i]);
	}
	auto add=[&](ll x,ll v)->void{
		for(;x<=cnt;x+=x&-x)
			bit[x]+=v;
	};
	auto sum=[&](ll x)->ll{
		ll res=0;
		for(;x;x-=x&-x)
			res+=bit[x];
		return res;
	};

	cur[0]=1;
	for(ll i=(ll)eg[0].size()-1;i>=0;i--)
		stk.emplace(eg[0][i]);
	while(!stk.empty()){
		ll u=stk.top();
		stk.pop();
		if(u<0){
			add(dfn[cur[-u]],-1);
			continue;
		}
		cur[u]=nxt[cur[fa[u]]][val[u]];
		add(dfn[cur[u]],1);
		for(ll i=0;i<(ll)ask[u].size();i++){
			ll p=ask[u][i].first,id=ask[u][i].second;
			ans[id]=sum(out[p])-sum(dfn[p]-1);
		}
		stk.emplace(-u);
		for(ll i=(ll)eg[u].size()-1;i>=0;i--)
			stk.emplace(eg[u][i]);
	}
	for(ll i=0;i<m;i++)
		cout<<ans[i]<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
