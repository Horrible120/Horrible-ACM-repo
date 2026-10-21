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
	vector<vector<ll>> eg(n+1,vector<ll>());
	
	vector<ll> du(n+1,0);
	
	for(ll i=1;i<n;i++){
		ll u,v;
		cin>>u>>v;
		eg[u].emplace_back(v);
		eg[v].emplace_back(u);
		
		du[u]++;
		du[v]++;
		
	}
	
	vector<ll> book(n+1,0);
	
	ll st[2]={};
	
	for(ll i=1;i<=n;i++){
		for(auto v:eg[i]){
			book[i]+=(du[v]>1);
		}
		
		if(book[i]==1&&du[i]>1){
//			cout<<">>> "<<i<<endl;
			if(!st[0]) st[0]=st[1]=i;
			else st[1]=i;
		}
		
		if(book[i]>2){
			cout<<"No"<<endl;
			return;
		}
	}
	
	cout<<"Yes"<<endl;
	
	if(n<=2||st[0]==0){
		for(ll i=1;i<=n;i++){
			cout<<i<<' ';
		}
		cout<<endl;
		return;
	}
	vector<ll> ans(n+1,0);
	
	vector<ll> vis(n+1,0);
	
	ll l=1,r=n,u=st[0],cnt=0;
	while(1){
		++cnt;
		ll nxt=0;
//		cout<<st[0]<<endl;
		if(cnt%2==1){
			for(auto v:eg[u]){
				if(du[v]==1) ans[r--]=v,vis[v]=1;
				else if(!vis[v]) nxt=v;
			}
			vis[u]=1;
			ans[l++]=u;
			u=nxt;
		}else{
			for(auto v:eg[u]){
				if(du[v]==1) ans[l++]=v,vis[v]=1;
				else if(!vis[v]) nxt=v;
			}
			vis[u]=1;
			ans[r--]=u;
			u=nxt;
		}
		
		if(nxt==0) break;
	}
	
	for(ll i=1;i<=n;i++){
		cout<<ans[i]<<' ';
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
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
