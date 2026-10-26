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
	vector<ll> val(n+1),sum(n+1),mx(n+1),cnt(k);
	for(ll i=1;i<=n;i++){
		cin>>val[i];
		sum[i]=(sum[i-1]+val[i])%k;
	}

	ll ans=0;
	auto dfs=[&](this auto &&self,ll l,ll r)->void{
		if(l==r)
			return;
		ll mid=(l+r)/2;
		self(l,mid);
		self(mid+1,r);

		mx[mid]=val[mid];
		for(ll i=mid-1;i>=l;i--)
			mx[i]=max(mx[i+1],val[i]);
		mx[mid+1]=val[mid+1];
		for(ll i=mid+2;i<=r;i++)
			mx[i]=max(mx[i-1],val[i]);

		ll p=mid;
		for(ll i=mid;i>=l;i--){
			while(p<r&&mx[p+1]<=mx[i]){
				p++;
				cnt[sum[p]]++;
			}
			ans+=cnt[(sum[i-1]+mx[i])%k];
		}
		for(ll i=mid+1;i<=p;i++)
			cnt[sum[i]]--;

		p=mid+1;
		for(ll i=mid+1;i<=r;i++){
			while(p>l&&mx[p-1]<mx[i]){
				p--;
				cnt[sum[p-1]]++;
			}
			ans+=cnt[(sum[i]-mx[i]%k+k)%k];
		}
		for(ll i=p;i<=mid;i++)
			cnt[sum[i-1]]--;
	};
	dfs(1,n);
	cout<<ans<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
