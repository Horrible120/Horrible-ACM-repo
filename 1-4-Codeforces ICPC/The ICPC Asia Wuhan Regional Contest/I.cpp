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
	vector<ll> cnt(n+1,0);
	
	ll flag=0,csum=0,mx=0;
	
	for(ll i=1;i<=n;i++){
		cin>>cnt[i];
		csum+=cnt[i];
		mx=max(cnt[i],mx);
		flag+=(cnt[i]==0);
	}
	
	if(k<flag){
		cout<<n-flag+k<<endl;
		return;
	}
	
	k-=flag;
	
	for(ll i=1;i<=n;i++){
		cnt[i]=max(cnt[i]-1,0ll);
	}
	
	sort(cnt.begin()+1,cnt.end());
	
	auto check=[&](ll x)->bool{
		ll sum=0;
		for(ll i=1;i<=n;i++){
			sum+=max(0ll,x-1-cnt[i]);
		}
		if(sum<=x-1&&max(0ll,x-1-cnt[1])<=x/2){
			return true;
		}
		return false;
	};
	
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
