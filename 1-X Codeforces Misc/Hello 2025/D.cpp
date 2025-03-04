#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;
ll v[1000010];

struct Node{
	ll lx,ln,rx,rn,key;
	Node(){
		lx=ln=rx=rn=key=-INF;
	}
}sgm_tree[1000010];

void build_tree(ll x,ll l,ll r){
	Node &cur=sgm_tree[x];
	if(l==r){
		cur.lx=v[l]+l;
		cur.ln=-v[l]+l;
		cur.rx=v[l]-l;
		cur.rn=-v[l]-l;
		cur.key=0;
	}
	else{
		ll mid=(l+r)/2;
		build_tree(x*2,l,mid);
		build_tree(x*2+1,mid+1,r);
		
		cur.lx=max(sgm_tree[x*2].lx,sgm_tree[x*2+1].lx);
		cur.ln=max(sgm_tree[x*2].ln,sgm_tree[x*2+1].ln);
		cur.rx=max(sgm_tree[x*2].rx,sgm_tree[x*2+1].rx);
		cur.rn=max(sgm_tree[x*2].rn,sgm_tree[x*2+1].rn);
		
		cur.key=max(max(sgm_tree[x*2].key,sgm_tree[x*2+1].key),
			max(sgm_tree[x*2].ln+sgm_tree[x*2+1].rx,
				sgm_tree[x*2].lx+sgm_tree[x*2+1].rn));
		
	}
	
}

void change(ll x,ll l,ll r,ll tg){
	Node &cur=sgm_tree[x];
	if(l==r){
		cur.lx=v[l]+l;
		cur.ln=-v[l]+l;
		cur.rx=v[l]-l;
		cur.rn=-v[l]-l;
		cur.key=0;
	}
	else{
		ll mid=(l+r)/2;
		if(tg<=mid) change(x*2,l,mid,tg);
		else change(x*2+1,mid+1,r,tg);
		
		cur.lx=max(sgm_tree[x*2].lx,sgm_tree[x*2+1].lx);
		cur.ln=max(sgm_tree[x*2].ln,sgm_tree[x*2+1].ln);
		cur.rx=max(sgm_tree[x*2].rx,sgm_tree[x*2+1].rx);
		cur.rn=max(sgm_tree[x*2].rn,sgm_tree[x*2+1].rn);
		
		cur.key=max(max(sgm_tree[x*2].key,sgm_tree[x*2+1].key),
			max(sgm_tree[x*2].ln+sgm_tree[x*2+1].rx,
				sgm_tree[x*2].lx+sgm_tree[x*2+1].rn));
		
	}
}

ll get_max(ll x,ll l,ll r,ll s,ll t){
	Node &cur=sgm_tree[x];
	if(l>=s&&r<=t){
		return cur.key;
	}
	else{
		ll mid=(l+r)/2,res=0;
		if(mid>=s) res=max(res,get_max(x*2,l,mid,s,t));
		if(mid+1<=t) res=max(res,get_max(x*2+1,mid+1,r,s,t));
		return res;
	}
}

void solve(){
	ll n,q;
	cin>>n>>q;
	for(ll i=1;i<=n;i++) cin>>v[i];
	for(ll i=1;i<=4*n+1;i++) sgm_tree[i]=Node();
	build_tree(1,1,n);
//	OOO
	cout<<get_max(1,1,n,1,n)<<endl;
	for(ll i=1;i<=q;i++){
		ll x,p;
		cin>>x>>p;
		v[x]=p;
		change(1,1,n,x);
//		OOO
		cout<<get_max(1,1,n,1,n)<<endl;
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
