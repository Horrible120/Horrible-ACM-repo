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
	map<ll,ll> cnta,cntb;
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		cnta[x]++;
	}
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		cntb[x]++;
	}

	vector<pair<ll,ll>> grp;
	for(auto p:cntb)
		grp.emplace_back(p.first,p.second);
	sort(grp.begin(),grp.end(),[](auto x,auto y){
		return x.first-x.second<y.first-y.second;
	});

	ll m=grp.size(),sum=0,i=0;
	while(i<m&&grp[i].first<=sum+grp[i].second){
		sum+=grp[i].second;
		i++;
	}
	for(ll j=i;j<m;j++){
		if(cnta[grp[j].first]<grp[j].second){
			cout<<"NO\n";
			return;
		}
	}

	cout<<"YES\n";
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
