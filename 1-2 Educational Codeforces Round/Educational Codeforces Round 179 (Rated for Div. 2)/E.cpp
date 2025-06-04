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

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,q;
	cin>>n>>q;
	string s;
	cin>>s;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		v[i]=s[i-1]-'a';
	}
	
	set<ll> op[3][3];
	
	for(ll i=1;i<=q;i++){
		string x,y;
		cin>>x>>y;
		op[x[0]-'a'][y[0]-'a'].insert(i);
	}
	
	for(ll i=1;i<=n;i++){
		if(v[i]==0)
			continue;
		else if(v[i]==1){
			if(op[1][0].size()){
				op[1][0].erase(op[1][0].begin());
				v[i]=0;
			}
			else if(op[1][2].size()&&op[2][0].size()){
				ll a=*op[1][2].begin();
				if(op[2][0].lower_bound(a)!=op[2][0].end()){
					op[1][2].erase(op[1][2].begin());
					op[2][0].erase(op[2][0].lower_bound(a));
					v[i]=0;
				}
			}
		}
		else if(v[i]==2){
			if(op[2][0].size()){
				op[2][0].erase(op[2][0].begin());
				v[i]=0;
				continue;
			}
			if(op[2][1].size()&&op[1][0].size()){
				ll a=*op[2][1].begin();
				if(op[1][0].lower_bound(a)!=op[1][0].end()){
					op[2][1].erase(op[2][1].begin());
					op[1][0].erase(op[1][0].lower_bound(a));
					v[i]=0;
					continue;
				}
			}
			if(op[2][1].size()){
				op[2][1].erase(op[2][1].begin());
				v[i]=1;
			}
		}
	}
	
	string ans;
	for(ll i=1;i<=n;i++){
		ans+=(char)('a'+v[i]);
	}
	cout<<ans<<endl;
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
