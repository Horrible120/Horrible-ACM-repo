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
	vector<vector<ll>> eg(n+1);
	vector<ll> prex(200001),prey(200001);
	for(ll i=1;i<=n;i++){
		ll x,y;
		cin>>x>>y;
		if(prex[x]){
			eg[i].emplace_back(prex[x]);
			eg[prex[x]].emplace_back(i);
			prex[x]=0;
		}else
			prex[x]=i;

		if(prey[y]){
			eg[i].emplace_back(prey[y]);
			eg[prey[y]].emplace_back(i);
			prey[y]=0;
		}else
			prey[y]=i;
	}

	vector<ll> col(n+1,-1);
	queue<ll> que;
	for(ll i=1;i<=n;i++){
		if(col[i]!=-1)
			continue;
		col[i]=0;
		que.emplace(i);
		while(!que.empty()){
			ll u=que.front();
			que.pop();
			for(ll j=0;j<(ll)eg[u].size();j++){
				ll v=eg[u][j];
				if(col[v]!=-1)
					continue;
				col[v]=col[u]^1;
				que.emplace(v);
			}
		}
	}

	for(ll i=1;i<=n;i++)
		cout<<(col[i]?'b':'r');
	cout<<'\n';
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
