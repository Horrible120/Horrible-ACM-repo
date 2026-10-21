#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
//using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;

typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

//template <typename T, typename Compare = std::less<T>>
//using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll a,b,c;
	cin>>a>>b>>c;
	ll g=__lg(b)+1;
	
//	cout<<"!!! "<<g<<endl;
	
	ll n=(1<<g);
	
	auto gid=[&](ll x,ll y)->ll{
		return x*n+y;
	};
	
	priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> que;
	vector<ll> dis(n*b+1,INF),vis(n*b+1,0);
	
	que.push(make_pair(a,gid(a%b,a&(n-1))));
	dis[gid(a%b,a&(n-1))]=a;
	vis[gid(a%b,a&(n-1))]=0;
	
	ll t1,t2;
	
	while(que.size()){
		ll u=que.top().second;
		
		que.pop();
		if(vis[u]) continue;
		vis[u]=1;
		
		t1=u/n;
		t2=u%n;
		
//		cout<<"!! "<<t1<<' '<<t2<<' '<<dis[u]<<endl;
		
		ll v=gid(t1,(t2+b)&(n-1));
		
		if(dis[v]>dis[u]+b){
			dis[v]=dis[u]+b;
			que.push(make_pair(dis[v],v));
		}
		
		v=gid((t1+((t2^b)-t2)+2*b)%b,t2^b);
		
		if(dis[v]>(dis[u]^b)){
			dis[v]=dis[u]^b;
			que.push(make_pair(dis[v],v));
		}
	}
	
	ll ans=0;
	for(ll i=0;i<n;i++){
		if(dis[gid(c%b,i)]<=c){
			ans=1;
		}
	}
	cout<<(ans==1?"YES":"NO")<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cout<<__lg(2)<<endl;
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
