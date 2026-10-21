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
	ll cur;
	cin>>cur;
	
	ll max_val=cur;
	
	for(ll i=1;i<=300;i++){
		cout<<"+ "<<rnd()%998244353+1<<endl;
		cin>>cur;
		max_val=max(max_val,cur);
	}
	
	ll k=122500;
	
	map<ll,ll> mp;
	
	mp[cur]=0;
	
	for(ll i=1;i<=350;i++){
		cout<<"+ 1"<<endl;
		cin>>cur;
		
		if(mp.count(cur)){
			cout<<"! "<<i-mp[cur]<<endl;
			return;
		}
		
		mp[cur]=i;
	}
	
	for(ll i=1;i<=350;i++){
		if(i==1){
			cout<<"+ "<<max_val<<endl;
		}else{
			cout<<"+ "<<350<<endl;
		}
		
		cin>>cur;
		
		if(mp.count(cur)){
			cout<<"! "<<max_val+350*i-mp[cur]<<endl;
			return;
		}
		
		mp[cur]=max_val+350*i;
	}
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
