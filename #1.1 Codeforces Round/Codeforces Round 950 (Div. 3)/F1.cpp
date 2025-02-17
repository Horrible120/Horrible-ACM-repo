#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,m,k,sum=0;
	cin>>n>>m>>k;
	vector<pair<ll,ll>> funt(k+1);
	vector<ll> ans(k+1);
	map<pair<ll,ll>,ll> mp;
	for(ll i=1;i<=k;i++){
		auto &[x,y]=funt[i];
		cin>>x>>y;
		mp[make_pair(x,y)]=i;
	}
	auto cmp=[](pair<ll,ll> a,pair<ll,ll> b){
		if(a.second!=b.second) return a.second<b.second;
		else return a.first>b.first;
	};
	sort(funt.begin()+1,funt.end(),cmp);
	pair<ll,ll> last=make_pair(0,1);
	for(ll i=1;i<=k;i++){
		if(i>1&&funt[i].second==funt[i-1].second) continue;
		auto &[r,c]=funt[i];
		if(r<=last.first) continue;
		ans[mp[make_pair(r,c)]]=1;
		sum+=(r-last.first)*(c-1);
		last=funt[i];
	}
	sum+=(n-last.first)*m;
//	OOO
	cout<<sum<<endl;
	for(ll i=1;i<=k;i++) cout<<ans[i]<<' ';
	cout<<endl;
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
