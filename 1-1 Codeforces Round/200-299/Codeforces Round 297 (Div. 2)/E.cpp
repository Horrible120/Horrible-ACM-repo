#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

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
	ll n,k,S,ans=0;
	cin>>n>>k>>S;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	vector<ll> fct(21,0);
	fct[0]=1;
	for(ll i=1;i<=20;i++)
		fct[i]=fct[i-1]*i;
	
	ll m=n/2;
	
	vector<unordered_map<ll,ll>> mp(k+1);
	
	
	auto DFS1=[&](auto &&self,ll x,ll sum,ll cnt)->void{
		if(cnt>k||sum>S)
			return;
		if(x>m){
			mp[cnt][sum]++;
			return;
		}
		
		if(v[x]<=18)
			self(self,x+1,sum+fct[v[x]],cnt+1);
		
		self(self,x+1,sum+v[x],cnt);
		self(self,x+1,sum,cnt);
	};
	
	DFS1(DFS1,1,0,0);
	
	auto DFS2=[&](auto &&self,ll x,ll sum,ll cnt)->void{
		if(cnt>k||sum>S)
			return;
		if(x>n){
			for(ll i=0;i<=k-cnt;i++)
				if(mp[i][S-sum])
					ans+=mp[i][S-sum];
			return;
		}
		
		if(v[x]<=18)
			self(self,x+1,sum+fct[v[x]],cnt+1);
		
		self(self,x+1,sum+v[x],cnt);
		self(self,x+1,sum,cnt);
	};
	
	DFS2(DFS2,m+1,0,0);
	
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
