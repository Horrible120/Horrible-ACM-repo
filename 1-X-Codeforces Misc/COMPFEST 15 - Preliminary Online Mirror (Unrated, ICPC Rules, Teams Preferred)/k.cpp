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
	vector<vector<array<ll,2>>> eg(n+1,vector<array<ll,2>>());
	
	for(ll i=1;i<n;i++){
		ll u,v,w;
		cin>>u>>v>>w;
		eg[u].emplace_back(array<ll,2>{v,w});
		eg[v].emplace_back(array<ll,2>{u,w});
	}
	
	ll dim=0;
	vector<array<ll,2>> d(n+1,{{}});
	vector<ll> fa(n+1,0),g(n+1,0);
	
	auto DFS1=[&](this auto &&self,ll u)->void{
		for(auto [v,w]:eg[u]){
			if(v!=fa[u]){
				fa[v]=u;
				self(v);
				ll len=d[v][0]+w;
				if(len>d[u][0]) swap(len,d[u][0]);
				d[u][1]=max(d[u][1],len);
			}
		}
	};
	
	auto DFS2=[&](this auto &&self,ll u)->void{
		dim=max(dim,d[u][0]+max(d[u][1],g[u]));
		for(auto [v,w]:eg[u]) if(v!=fa[u]){
			g[v]=max(d[v][0]+w==d[u][0]?d[u][1]+w:d[u][0]+w,g[u]+w);
			self(v);
		}
	};
	
	fa[1]=1;
	DFS1(1);
	DFS2(1);
	
	vector<vector<array<ll,2>>> conv(n+1,vector<array<ll,2>>()),convv(n+1,vector<array<ll,2>>());;
	vector<ll> top(n+1,0),ttop(n+1,0);
	
	for(ll u=1;u<=n;u++){
		vector<array<ll,2>> tmp,ttmp;
		for(auto [v,w]:eg[u]){
			if(v==fa[u]){
				tmp.emplace_back(array<ll,2>{w,g[u]-w});
			}else{
				tmp.emplace_back(array<ll,2>{w,d[v][0]});
			}
		}
		
		sort(tmp.begin(),tmp.end());
		
		auto &tp=top[u];
		auto &ttp=ttop[u];
		auto &cv=conv[u];
		auto &cvv=convv[u];
		
		cv.assign(tmp.size()+1,array<ll,2>());
		cvv.assign(tmp.size()+1,array<ll,2>());
		
		
		for(auto [k,b]:tmp){
			if (tp >= 1 && cv[tp][0] == k){
				ttmp.emplace_back(cv[tp--]);
			}
			while(tp>=2){
				if((__int128)(cv[tp][0]-k)*(cv[tp][1]-cv[tp-1][1])>=(__int128)(cv[tp-1][0]-cv[tp][0])*(b-cv[tp][1])){
					ttmp.emplace_back(cv[tp--]);
				}else{
					break;
				}
			}
			cv[++tp]={{k,b}};
		}
		
		sort(ttmp.begin(),ttmp.end());
		
		for(auto [k,b]:ttmp){
			if (ttp >= 1 && cvv[ttp][0] == k){
				ttp--;
			}
			while(ttp>=2){
				if((__int128)(cvv[ttp][0]-k)*(cvv[ttp][1]-cvv[ttp-1][1])>=(__int128)(cvv[ttp-1][0]-cvv[ttp][0])*(b-cvv[ttp][1])){
					ttp--;
				}else{
					break;
				}
			}
			cvv[++ttp]={{k,b}};
		}
		
	}
	
	auto cal=[&](array<ll,2> ln,ll x)->ll{
		return ln[0]*x+ln[1];
	};
	
	auto get_max=[&](vector<array<ll,2>> &cv,ll &tp,ll x)->ll{
		ll l=1,r=tp;
		while(l<r){
			ll mid=l+r>>1LL;
			if(cal(cv[mid],x)<=cal(cv[mid+1],x)){
				l=mid+1;
			}else{
				r=mid;
			}
		}
		return l;
	};
	
	ll q;
	cin>>q;
	while(q--){
		ll x,k;
		cin>>x>>k;
		ll p[2]={get_max(conv[x],top[x],k),get_max(convv[x],ttop[x],k)};
		ll tmp=cal(conv[x][p[0]],k)+max(cal(convv[x][p[1]],k),max((p[0]>1?cal(conv[x][p[0]-1],k):0LL),(p[0]<top[x]?cal(conv[x][p[0]+1],k):0LL)));
		cout<<max(tmp,dim)<<'\n';
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
