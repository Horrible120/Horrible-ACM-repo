#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll L,W,H;
	cin>>L>>W>>H;
	
	ll p,q,r;
	cin>>p>>q>>r;
	
	ll n;
	cin>>n;
	
	vector<ll> x(n+1,0),y(n+1,0),z(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>x[i]>>y[i]>>z[i];
	}
	
	ll ans=1;
	
	if(n%((p+1)*(q+1)*(r+1))){
		cout<<0<<endl;
		return;
	}
	
	vector<ll> vx(n+1,0),vy(n+1,0),vz(n+1,0);
	
	auto xcmp=[&](const ll &aa,const ll &bb)->bool{
		return x[aa]<x[bb];
	};
	
	auto ycmp=[&](const ll &aa,const ll &bb)->bool{
		return y[aa]<y[bb];
	};
	
	auto zcmp=[&](const ll &aa,const ll &bb)->bool{
		return z[aa]<z[bb];
	};
	
	for(ll i=1;i<=n;i++){
		vx[i]=vy[i]=vz[i]=i;
	}
	
//	OOO
	
	sort(vx.begin()+1,vx.end(),xcmp);
	sort(vy.begin()+1,vy.end(),ycmp);
	sort(vz.begin()+1,vz.end(),zcmp);
	
	ll pc=n/(p+1)/(q+1)/(r+1);
	
	for(ll i=1;i<=n;i+=(q+1)*(r+1)*pc){
		if(i>1) ans=ans*(x[vx[i]]-x[vx[i-1]])%Mod;
	}
	
	for(ll i=1;i<=n;i+=(p+1)*(r+1)*pc){
		if(i>1) ans=ans*(y[vy[i]]-y[vy[i-1]])%Mod;
	}
	
	for(ll i=1;i<=n;i+=(p+1)*(q+1)*pc){
		if(i>1) ans=ans*(z[vz[i]]-z[vz[i-1]])%Mod;
	}
	
//	OOO
	
//	OOO
	
	for(ll i=1;i<=n;i+=(q+1)*(r+1)*pc){
		sort(vx.begin()+i,vx.begin()+i+(q+1)*(r+1)*pc,ycmp);
		for(ll k=1;k<q+1;k++){
			if(y[vx[i-1+k*(r+1)*pc]]>y[vy[k*(p+1)*(r+1)*pc]]) ans=0;
			if(y[vx[i+k*(r+1)*pc]]<y[vy[k*(p+1)*(r+1)*pc+1]]) ans=0;
		}
		for(ll j=i;j<i+(q+1)*(r+1)*pc;j+=(r+1)*pc){
			sort(vx.begin()+j,vx.begin()+j+(r+1)*pc,zcmp);
			for(ll k=1;k<r+1;k++){
				if(z[vx[j-1+k*pc]]>z[vz[k*(q+1)*(p+1)*pc]]) ans=0;
				if(z[vx[j+k*pc]]<z[vz[k*(q+1)*(p+1)*pc+1]]) ans=0;
			}
		}
	}
	
//	OOO
	cout<<ans<<endl;
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
