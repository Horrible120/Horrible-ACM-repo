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

struct Info{
	ll d[2]={INF,INF}, r[2]={-1,-1};
};

Info calc(const vct<ll> &a){
	ll len=a.size();
	vct<ll> to(len),vis(len);
	Info res;
	for(ll r=0;r<len;r++){
		for(ll i=0;i<len;i++){
			to[a[i]]=(i-r+len)%len;
			vis[i]=0;
		}
		ll cnt=0;
		for(ll i=0;i<len;i++){
			if(vis[i]) continue;
			ll x=i,sz=0;
			while(!vis[x]){
				vis[x]=1;
				sz++;
				x=to[x];
			}
			if(i==0) cnt+=sz-1;
			else if(sz>1) cnt+=sz+1;
		}
		ll p=cnt&1;
		if(cnt<res.d[p]){
			res.d[p]=cnt;
			res.r[p]=r;
		}
	}
	return res;
}

vct<ll> build(vct<ll> a,ll r){
	ll len=a.size();
	vct<ll> b(len),pos(len),res;
	for(ll i=0;i<len;i++){
		b[i]=(i-r+len)%len;
		pos[a[i]]=i;
	}
	auto change=[&](ll x){
		ll u=pos[0],v=pos[x];
		res.push_back((v-u+len)%len);
		swap(a[u],a[v]);
		pos[x]=u;
		pos[0]=v;
	};
	while(b[pos[0]]) change(b[pos[0]]);
	for(ll i=0;i<len;i++){
		if(a[i]==b[i]) continue;
		change(a[i]);
		while(b[pos[0]]) change(b[pos[0]]);
	}
	return res;
}

void solve(){
	ll n,m;
	cin>>n>>m;
	vct<ll> a(n+1),b(m+1);
	for(ll i=1;i<=n;i++) cin>>a[i];
	for(ll i=1;i<=m;i++) cin>>b[i];
	Info x=calc(a),y=calc(b);
	ll ans=INF,p=-1;
	for(ll i=0;i<2;i++){
		ll cur=max(x.d[i],y.d[i]);
		if(cur<ans){
			ans=cur;
			p=i;
		}
	}
	if(p==-1){
		cout<<-1<<'\n';
		return;
	}
	vct<ll> v=build(a,x.r[p]),w=build(b,y.r[p]);
	while((ll)v.size()<ans){
		v.push_back(1);
		v.push_back(n);
	}
	while((ll)w.size()<ans){
		w.push_back(1);
		w.push_back(m);
	}
	cout<<ans<<'\n';
	for(ll i=0;i<ans;i++) cout<<v[i]<<' '<<w[i]<<'\n';
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
