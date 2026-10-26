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
	ll n,q;
	cin>>n>>q;
	vector<vector<ll>> eg(n+1);
	vector<ll> fa(n+1),val(n+1),dis(n+1),out(n+1);
	for(ll i=2;i<=n;i++){
		cin>>fa[i]>>val[i];
		eg[fa[i]].emplace_back(i);
		dis[i]=dis[fa[i]]+val[i];
	}
	for(ll i=1;i<=n;i++)
		out[i]=i;
	for(ll i=n;i>=2;i--)
		out[fa[i]]=max(out[fa[i]],out[i]);

	vector<vector<array<ll,3>>> ask(n+1);
	vector<ll> ans(q);
	for(ll i=0;i<q;i++){
		ll u,l,r;
		cin>>u>>l>>r;
		ask[u].emplace_back(array<ll,3>{l,r,i});
	}

	vector<ll> mn(4*n+4),tag(4*n+4);
	auto build=[&](auto &&self,ll p,ll l,ll r)->void{
		if(l==r){
			mn[p]=eg[l].empty()?dis[l]:INF;
			return;
		}
		ll mid=(l+r)/2;
		self(self,p*2,l,mid);
		self(self,p*2+1,mid+1,r);
		mn[p]=min(mn[p*2],mn[p*2+1]);
	};
	auto apply=[&](ll p,ll v)->void{
		mn[p]+=v;
		tag[p]+=v;
	};
	auto push=[&](ll p)->void{
		apply(p*2,tag[p]);
		apply(p*2+1,tag[p]);
		tag[p]=0;
	};
	auto add=[&](auto &&self,ll p,ll l,ll r,ll ql,ll qr,ll v)->void{
		if(ql<=l&&r<=qr){
			apply(p,v);
			return;
		}
		push(p);
		ll mid=(l+r)/2;
		if(ql<=mid)
			self(self,p*2,l,mid,ql,qr,v);
		if(qr>mid)
			self(self,p*2+1,mid+1,r,ql,qr,v);
		mn[p]=min(mn[p*2],mn[p*2+1]);
	};
	auto query=[&](auto &&self,ll p,ll l,ll r,ll ql,ll qr)->ll{
		if(ql<=l&&r<=qr)
			return mn[p];
		push(p);
		ll mid=(l+r)/2,res=INF;
		if(ql<=mid)
			res=min(res,self(self,p*2,l,mid,ql,qr));
		if(qr>mid)
			res=min(res,self(self,p*2+1,mid+1,r,ql,qr));
		return res;
	};
	build(build,1,1,n);

	stack<ll> stk;
	stk.emplace(1);
	while(!stk.empty()){
		ll u=stk.top();
		stk.pop();
		if(u<0){
			u=-u;
			if(u!=1){
				add(add,1,1,n,u,out[u],2*val[u]);
				add(add,1,1,n,1,n,-val[u]);
			}
			continue;
		}
		if(u!=1){
			add(add,1,1,n,1,n,val[u]);
			add(add,1,1,n,u,out[u],-2*val[u]);
		}
		for(ll i=0;i<(ll)ask[u].size();i++)
			ans[ask[u][i][2]]=query(query,1,1,n,ask[u][i][0],ask[u][i][1]);

		stk.emplace(-u);
		for(ll i=(ll)eg[u].size()-1;i>=0;i--)
			stk.emplace(eg[u][i]);
	}

	for(ll i=0;i<q;i++)
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
