#include <bits/stdc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
//using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef int ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

//template <typename T, typename Compare = std::less<T>>
//using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1,tot=0;

class Info{
public:
	ll cnt,lhs,rhs;
};

Info tr[40000002];

void modify(ll &u,ll v,ll l,ll r,ll pos,ll set_to){
	u=++tot;
	tr[u]=tr[v];
	if(l==r){
		tr[u].cnt=set_to;
		return;
	}
	ll mid=(l+r)/2;
	if(pos<=mid)
		modify(tr[u].lhs,tr[v].lhs,l,mid,pos,set_to);
	else
		modify(tr[u].rhs,tr[v].rhs,mid+1,r,pos,set_to);
	tr[u].cnt=tr[tr[u].lhs].cnt+tr[tr[u].rhs].cnt;
}

ll query(ll u,ll l,ll r,ll s,ll t){
	if(!u)
		return 0;
	if(l>=s&&r<=t)
		return tr[u].cnt;
	ll mid=(l+r)/2,res=0;
	if(mid>=s)
		res+=query(tr[u].lhs,l,mid,s,t);
	if(mid<=t+1)
		res+=query(tr[u].rhs,mid+1,r,s,t);
	return res;
}

void solve(){
	ll n,m;
	cin>>n;
	vector<ll> v(n+1,0),lst(n+1,0),rt(n+1,0);
	vector<ll> last(1000010,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		lst[i]=last[v[i]];
		last[v[i]]=i;
	}
	
	for(ll i=1;i<=n;i++){
		modify(rt[i],rt[i-1],1,n,i,1);
		if(lst[i])
			modify(rt[i],rt[i],1,n,lst[i],0);
	}
	
	cin>>m;
	while(m--){
		ll l,r;
		cin>>l>>r;
		cout<<query(rt[r],1,n,l,r)<<'\n';
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
