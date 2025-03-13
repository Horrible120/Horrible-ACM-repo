#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,m,flag=0;
	cin>>n>>m;
	v2ct<ll> eg(n+1,vector<ll>());
	for(ll i=1;i<=m;i++){
		ll u,v;
		cin>>u>>v;
		eg[v].emplace_back(u);
		eg[u].emplace_back(v);
	}
	vector<ll> col(n+1),a,b;
	
	auto DFS=[&](auto &self,ll u)->void{
		if(col[u]==1)
			a.emplace_back(u);
		else
			b.emplace_back(u);
		for(auto v:eg[u]){
			if(!col[v]){
				col[v]=col[u]%2+1;
				self(self,v);
			}
			else if(col[v]==col[u])
				flag=1;
		}
	};
	
	for(ll i=1;i<=n;i++)
		if(!col[i]){
			col[i]=1;
			DFS(DFS,i);
		}
	
	if(flag){
		cout<<"Alice"<<endl;
		for(ll i=1;i<=n;i++)
			cout<<"1 2"<<endl,cin>>flag>>flag;
	}
	else{
		cout<<"Bob"<<endl;
		ll t1=a.size(),t2=b.size();
		for(ll i=1;i<=n;i++){
			ll c1,c2;
			cin>>c1>>c2;
			if(c1!=1&&c2!=1){
				if(t2)
					cout<<b[--t2]<<' '<<2<<endl;
				else
					cout<<a[--t1]<<' '<<3<<endl;
			}
			else if(c1!=2&&c2!=2){
				if(t1)
					cout<<a[--t1]<<' '<<1<<endl;
				else
					cout<<b[--t2]<<' '<<3<<endl;
			}
			else{
				if(t1)
					cout<<a[--t1]<<' '<<1<<endl;
				else
					cout<<b[--t2]<<' '<<2<<endl;
			}
		}
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
