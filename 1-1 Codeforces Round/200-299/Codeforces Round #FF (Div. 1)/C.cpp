#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+9;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;
ll F[300005];

class Info{
public:
	ll sum,a1,a2;
	
	Info()=default;
	
	Info(ll pos,ll val){
		a1=a2=0;
		sum=val;
	}
};

Info tr[300005*4+5];

void build_tree(ll u,ll l,ll r,vector<ll> &vals){
	if(l==r){
		tr[u]=Info(l,vals[l]);
		return;
	}
	
	ll mid=l+r>>1;
	build_tree(u*2,l,mid,vals);
	build_tree(u*2+1,mid+1,r,vals);
	tr[u].sum=(tr[u*2].sum+tr[u*2+1].sum)%Mod;
}

void push_down(ll u,ll l,ll r){
	if(tr[u].a1==0&&tr[u].a2==0)
		return;
	ll mid=l+r>>1;
	
	ll pref1=(tr[u].a1*F[mid-l+1]+tr[u].a2*(F[mid-l+2]-1))%Mod;
	ll pref2=(tr[u].a1*F[r-l+1]+tr[u].a2*(F[r-l+2]-1))%Mod;
	
	tr[u*2].a1=(tr[u*2].a1+tr[u].a1)%Mod;
	tr[u*2].a2=(tr[u*2].a2+tr[u].a2)%Mod;
	tr[u*2].sum=(tr[u*2].sum+pref1)%Mod;
	
	tr[u*2+1].a1=(tr[u*2+1].a1+tr[u].a1*F[mid-l]+tr[u].a2*F[mid-l+1])%Mod;
	tr[u*2+1].a2=(tr[u*2+1].a2+tr[u].a1*F[mid-l+1]+tr[u].a2*F[mid-l+2])%Mod;
	tr[u*2+1].sum=((tr[u*2+1].sum+pref2-pref1)%Mod+Mod)%Mod;
	
	tr[u].a1=0;
	tr[u].a2=0;
}

void modify(ll u,ll l,ll r,ll s,ll t){

	if(l>=s&&r<=t){
		tr[u].a1=(tr[u].a1+F[l-s+1])%Mod;
		tr[u].a2=(tr[u].a2+F[l-s+2])%Mod;
		tr[u].sum=((tr[u].sum+F[r-s+3]-F[l-s+2])%Mod+Mod)%Mod;
		return;
	}
	
//	cout<<u<<' '<<l<<' '<<r<<' '<<s<<' '<<t<<endl;
	
	push_down(u,l,r);
	
	ll mid=l+r>>1;
	if(mid>=s)
		modify(u*2,l,mid,s,t);
	if(mid+1<=t)
		modify(u*2+1,mid+1,r,s,t);
	
	tr[u].sum=(tr[u*2].sum+tr[u*2+1].sum)%Mod;
}

ll query(ll u,ll l,ll r,ll s,ll t){
	if(l>=s&&r<=t)
		return tr[u].sum;
	
	push_down(u,l,r);
	
	ll mid=l+r>>1,res=0;
	if(mid>=s)
		res+=query(u*2,l,mid,s,t);
	if(mid+1<=t)
		res+=query(u*2+1,mid+1,r,s,t);
	return res%Mod;
}

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	build_tree(1,1,n,v);
	
	for(ll i=1;i<=m;i++){
		ll op,x,y;
		cin>>op;
		if(op==1){
			cin>>x>>y;
			modify(1,1,n,x,y);
		}
		else{
			cin>>x>>y;
//			OOO
			cout<<query(1,1,n,x,y)<<endl;
		}
	}
	
	
} 

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	F[1]=1;
	F[2]=1;
	for(ll i=3;i<=300004;i++)
		F[i]=(F[i-1]+F[i-2])%Mod;
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
