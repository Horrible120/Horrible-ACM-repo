#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> b(2*n+1),pre(2*n+2),suf(2*n+2),ans(2*n+2);
	map<ll,ll> mp;
	
	for(ll i=1;i<=n*2;i++)
		cin>>b[i],mp[b[i]]=1;
	sort(b.begin()+1,b.end());
	ll tmp1=0,tmp2=0;
//	for(ll i=1;i<=n;i++){
//		tmp1+=b[i*2]-b[i*2-1];
//		tmp2+=b[n*2+1-i]-b[i];
//	}
	for(ll i=1;i<=n;i++){
		tmp2+=b[n*2+1-i]-b[i];
	}
	tmp2+=2*b[n];
//	if(mp[tmp1]==0){
//		cout<<tmp1<<' ';
//		for(ll i=1;i<=n;i++){
//			cout<<b[i*2]<<' '<<b[i*2-1]<<' ';
//		}
//		cout<<endl;
//	}
//	else{
//		cout<<tmp2<<' ';
//		for(ll i=1;i<=n;i++){
//			cout<<b[n*2+1-i]<<' '<<b[i]<<' ';
//		}
//		cout<<endl;
//	}
	for(ll i=0;i<=n;i++)
		ans[2*i+1]=b[2*n-i];
	for(ll i=1;i<=n-1;i++)
		ans[2*i]=b[i];
	ans[2*n]=tmp2;
	for(ll i=1;i<=n*2+1;i++)
		cout<<ans[i]<<' ';
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
