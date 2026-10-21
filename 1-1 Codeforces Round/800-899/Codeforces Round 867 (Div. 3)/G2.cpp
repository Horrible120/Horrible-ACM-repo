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

map<ll,ll> cnt;

void solve(){
	ll n;
	cin>>n;
	cnt.clear();
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		cnt[x]++;
	}
	
	ll ans=0;
	
	for(auto [v,ct]:cnt){
		ans+=ct*(ct-1)*(ct-2);
		if(v<=1000000){
			for(ll i=1;i*i<=v;i++){
				if(v%i==0){
					auto t1=cnt.find(v/i);
					if(i>1&&t1!=cnt.end()){
						auto t2=cnt.find(v*i);
						if(t2!=cnt.end()){
							ans+=ct*(t1->second)*(t2->second);
						}
					}
					if(i*i!=v){
						auto t1=cnt.find(i);
						if(t1!=cnt.end()){
							auto t2=cnt.find(v*v/i);
							if(t2!=cnt.end()){
								ans+=ct*(t1->second)*(t2->second);
							}
						}
					}
				}
			}
		}else{
			for(ll i=1;i*v<=1000000000;i++){
				if(i!=1&&v%i==0){
					if(cnt.count(v/i)&&cnt.count(v*i)){
						ans+=ct*cnt[v/i]*cnt[v*i];
					}
					if(i*i!=v){
						if(cnt.count(i)&&cnt.count(v*v/i)){
							ans+=ct*cnt[i]*cnt[v*v/i];
						}
					}
				}
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
