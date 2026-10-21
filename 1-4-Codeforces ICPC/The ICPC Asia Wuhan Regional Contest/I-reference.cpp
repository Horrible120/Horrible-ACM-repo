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
	vector<ll> a(n+1);
	ll tot=0;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		tot+=a[i];
	}

	auto check=[&](ll len){
		ll q=(len-1)/(n-1),rem=(len-1)%(n-1);
		ll low=(q+1)/2,cost=0,sum=0,cnt=0;
		for(ll i=1;i<=n;i++){
			cost+=max(0LL,low-a[i]);
			sum+=min(q,max(a[i],low));
			cnt+=a[i]>q;
		}
		return cost<=k&&sum+min(rem,cnt)+k-cost>=len;
	};

	ll l=n,r=tot+k;
	while(l<r){
		ll mid=(l+r+1)/2;
		if(check(mid))
			l=mid;
		else
			r=mid-1;
	}

	cout<<l<<'\n';
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
