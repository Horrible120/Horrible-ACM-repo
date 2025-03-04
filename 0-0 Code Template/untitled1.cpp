#include <bits/extc++.h>
//#define OOO print(">>>>");	//调试标识
//#define H_test(x) println("---> {} <---",x);	//调试输出

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
ll prm[200002];

void init(){
	for(ll i=2;i<=2e5;i++)
		prm[i]=i;
	for(ll i=2;i<=2e5;i++){
		if(prm[i]==i){
			for(ll j=i*2;j<=2e5;j+=i)
				prm[j]=min(prm[j],prm[i]);
		}
	}
	
}

void solve(){
	ll a,b;
	cin>>a>>b;
	if(a==1||b==1){
		cout<<-1<<endl;
		return;
	}
	ll ans=(prm[a]==prm[b]?prm[a]:prm[b]*prm[a]);
	map<ll,ll> mp;
	while(a>1){
		cout<<"!"<<prm[a]<<endl;
		mp[prm[a]]=1;
		a/=prm[a];
	}
	while(b>1){
		cout<<"!"<<prm[b]<<endl;
		if(mp[prm[b]]==1){
			ans=min(ans,prm[b]);
		};
		b/=prm[b];
	}
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	init();
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
