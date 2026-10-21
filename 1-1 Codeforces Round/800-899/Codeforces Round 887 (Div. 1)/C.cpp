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
	ll n,k,ans=0;
	cin>>n>>k;
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++) cin>>v[i],v[i]%=k;
	
	for(ll i=n-1;i>=0;i--){
		v[i+1]-=v[i];
		ans+=max(v[i+1],0LL);
	}
	
	multiset<ll> s1,s2;
	
	for(ll i=1;i<=n;i++){
		if(v[i]<0) s1.insert(v[i]);
		else if(v[i]>0){
			if(s1.size()&&*s1.begin()<v[i]-k){
				if(s2.size()&&v[i]-*s2.begin()>=v[i]-*s1.begin()-k){
					ans-=v[i]-*s2.begin();
					s2.erase(s2.begin());
					s2.insert(v[i]);
				}else{
					ans-=v[i]-*s1.begin()-k;
					s1.erase(s1.begin());
					s2.insert(v[i]);
				}
			}else if(s2.size()&&*s2.begin()<v[i]){
				ans-=v[i]-*s2.begin();
				s2.erase(s2.begin());
				s2.insert(v[i]);
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
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
