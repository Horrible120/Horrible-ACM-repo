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
	ll n,k;
	cin>>n>>k;
	vector<ll> a(n+1),b(n+1);
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<=n;i++)
		cin>>b[i];

	auto check=[&](ll x){
		std::priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> q;
		ll sum=0,cnt=0;
		for(ll i=1;i<=n;i++){
			q.emplace(a[i]-x,0);
			auto [v,t]=q.top();
			ll d=v+b[i];
			if(d>0)
				continue;

			sum+=d;
			if(t==0)
				cnt++;
			q.pop();
			q.emplace(-b[i],1);
		}
		return pair<ll,ll>{sum,cnt};
	};

	ll l=0,r=0;
	for(ll i=1;i<=n;i++)
		r=max(r,2*max(a[i],b[i]));

	while(l<r){
		ll mid=(l+r)/2;
		if(check(mid).second>=k)
			r=mid;
		else
			l=mid+1;
	}

	cout<<check(l).first+l*k<<'\n';
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
