#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,k,ans=0,cnt=0;
	cin>>n>>k;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		if(v[i]==1) ++cnt;
		if(i>1) ans+=(__gcd(v[i],v[i-1])==1);
	}
	
	if(cnt==n){
//		OOO
		cout<<n-k<<endl;
		return;
	}
	
	for(ll i=2;i<n&&k>0;i++){
		if(__gcd(v[i],v[i-1])==1&&__gcd(v[i],v[i+1])==1&&v[i-1]!=1&&v[i+1]!=1){
			k--;
			ans-=2;
			v[i]=0;
		}
	}
	
	multiset<ll> s;
	
	for(ll i=1;i<=n;i++){
		if(v[i]==1){
			ll tmp=i;
			while(tmp<n&&v[tmp+1]==1) ++tmp;
			if(i>1&&tmp<n) s.insert(tmp-i+1);
			i=tmp;
		}
	}
	
	while(s.size()&&k>=*s.begin()){
		k-=*s.begin();
		ans-=*s.begin()+1;
		s.erase(s.begin());
	}
	
//	OOO
	cout<<max(ans-k,0ll)<<endl;
	
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
