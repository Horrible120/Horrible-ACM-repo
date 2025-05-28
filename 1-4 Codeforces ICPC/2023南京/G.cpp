#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,m,k;
	cin>>n>>m>>k;
	vector<pair<ll,ll>> v(n+1);
	
	for(ll i=1;i<=n;i++)
		cin>>v[i].first>>v[i].second;
	
	struct cmp{
		bool operator()(const pair<ll,ll> &a,const pair<ll,ll> &b)const{
			if(a.first!=b.first)
				return a.first<b.first;
			return a.second>b.second;
		}
	};
	
	sort(v.begin()+1,v.end(),cmp());
	
	vector<ll> dp(m+1,0),max_w(n+1,0);
	
	for(ll i=1;i<=n;i++){
		for(ll j=m;j>=0;j--){
			if(j>=v[i].first)
				dp[j]=max(dp[j],dp[j-v[i].first]+v[i].second);
			max_w[i]=max(max_w[i],dp[j]);
		}
	}
	
	ll bonus=0,ans=0;
	multiset<ll> s;
	
	for(ll i=n;i>=0;i--){
		ans=max(ans,max_w[i]+bonus);
		if(s.size()<k){
			s.insert(v[i].second);
			bonus+=v[i].second;
		}
		else if(s.size()&&*s.begin()<v[i].second){
			bonus-=*s.begin();
			s.erase(s.begin());
			bonus+=v[i].second;
			s.insert(v[i].second);
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
