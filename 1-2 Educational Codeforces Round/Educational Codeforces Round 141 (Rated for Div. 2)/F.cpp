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
	ll n;
	cin>>n;
	
	vector<ll> a(n+1,0),b(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	for(ll i=1;i<=n;i++){
		cin>>b[i];
	}
	
//	ll n1,n2;
//	n1=n2=n;
	
	vector<ll> faa(n+1,0),fab(n+1,0);
	for(ll i=1;i<=n;i++){
		faa[i]=fab[i]=i;
	}
	
	auto getfa=[&](auto &&self,vector<ll> &fa,ll x)->ll{
		if(fa[x]==x){
			return fa[x];
		}else{
			return fa[x]=self(self,fa,fa[x]);
		}
	};
	
	auto join=[&](ll x,ll y,vector<ll> &fa){
		ll fax=getfa(getfa,fa,x);
		ll fay=getfa(getfa,fa,y);
		if(fax==fay){
			return;
		}
		fa[fay]=fax;
	};
	
	for(ll i=1;i<=n;i++){
		join(i,a[i],faa);
		join(i,b[i],fab);
	}
	
	vector<vector<ll>> edge(2*n+1,vector<ll>());
	
	for(ll i=1;i<=n;i++){
		edge[getfa(getfa,faa,i)].emplace_back(getfa(getfa,fab,i));
	}
	
	for(ll i=1;i<=n;i++){
		sort(edge[i].begin(),edge[i].end());
		edge[i].erase(unique(edge[i].begin(),edge[i].end()),edge[i].end());
//		cout<<i<<": ";
//		for(auto it:edge[i]){
//			cout<<it<<' ';
//		}
//		cout<<endl;
	}
	
	vector<ll> pl(n+1,0),pr(n+1,0),vis(n+1,0),pre(n+1,0);
	
	
	auto flip=[&](ll x){
		while(x){
			pr[x]=pre[x];
			swap(x,pl[pre[x]]);
		}
	};
	
	auto BFS=[&](ll x)->bool{
		queue<ll> q;
		vector<ll> vs(n+1,0);
		q.push(x);
		
		pl[x]=0;
		
		while(q.size()){
			ll u=q.front();
			q.pop();
			for(auto v:edge[u]){
				if(!vs[v]){
					vs[v]=1;
					pre[v]=u;
					if(!pr[v]){
						flip(v);
						return true;
					}
					q.push(pr[v]);
				}
			}
		}
		return 0;
	};
	
	ll ans=0;
	for(ll i=1;i<=n;i++){
		if(!vis[getfa(getfa,faa,i)]){
			vis[getfa(getfa,faa,i)]=1;
			ans+=BFS(getfa(getfa,faa,i));
		}
	}
	
//	for(ll i=1;i<=n;i++){
//		cout<<i<<' '<<pl[i]<<endl;
//	}
	
	vector<ll> v1(n+1,0),v2(n+1,0);
	
	cout<<n-ans<<endl;
	for(ll i=1;i<=n;i++){
		if(v1[getfa(getfa,faa,i)]==0&&v2[getfa(getfa,fab,i)]==0&&pl[getfa(getfa,faa,i)]==getfa(getfa,fab,i)){
			v1[getfa(getfa,faa,i)]=v2[getfa(getfa,fab,i)]=1;
			continue;
		}else{
			cout<<i<<' ';
		}
	}
	
	cout<<endl;
	
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
