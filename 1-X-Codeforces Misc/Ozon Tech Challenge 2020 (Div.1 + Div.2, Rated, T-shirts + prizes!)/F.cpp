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
	ll n,ans=INF;
	cin>>n;
	
	unordered_map<ll,ll> vis;
	
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	for(ll i=1;i<=n;i++){
		swap(v[i],v[rnd()%n+1]);
	}
	
	ll max_f=1e6;
	
	for(ll i=1;i<=min(50ll,n);i++){
		for(ll ttmp=v[i]-1;ttmp<=v[i]+1;ttmp++){
			ll tmp=ttmp;
			if(tmp<=0){
				continue;
			}
			
			vector<ll> prm;
			
			for(ll k=2;k<=min(tmp,max_f)&&tmp>1;k++){
				if(tmp%k==0){
					prm.emplace_back(k);
					while(tmp%k==0){
						tmp/=k;
					}
				}
			}
			
			if(tmp>1){
				prm.emplace_back(tmp);
			}
			
			for(auto it:prm){
				if(vis[it]) continue;
				
				vis[it]=1;
				ll cnt=0;
				for(ll j=1;j<=n;j++){
					if(v[j]<=it)
						cnt+=it-v[j];
					else
						cnt+=min(v[j]%it,it-v[j]%it);
				}
					
//				cout<<it<<' '<<cnt<<endl;
				
				ans=min(ans,cnt);
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
