#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	string s;
	cin>>s;
	ll n=s.size();
	
	ll idx=137;
	
	vector<ll> pre_hs(n+1,0),suf_hs(n+2,0),pw(n+1,0);
	
	pw[0]=1;
	for(ll i=1;i<=n;i++)
		pw[i]=pw[i-1]*idx%Mod;
	
	for(ll i=1;i<=n;i++)
		pre_hs[i]=(pre_hs[i-1]*idx+s[i-1]-'a')%Mod;
	
	for(ll i=n;i>=1;i--)
		suf_hs[i]=(suf_hs[i+1]*idx+s[i-1]-'a')%Mod;
	
//	cout<<">>> "<<(pre_hs[n]-pw[n-2]*pre_hs[2]%Mod+Mod)%Mod<<' '<<suf_hs[n-2+1]<<endl;
	
	if(pre_hs[n]!=suf_hs[1]){
		cout<<"YES\n"<<"1\n"<<s<<endl;
		return;
	}
	else{
		for(ll i=1;i<n;i++){
			if(pre_hs[i]!=(suf_hs[1]-pw[i]*suf_hs[i+1]%Mod+Mod)%Mod&&
				(pre_hs[n]-pw[n-i]*pre_hs[i]%Mod+Mod)%Mod!=suf_hs[i+1]){
				cout<<"YES\n"<<"2\n";
				cout<<s.substr(0,i)<<' '<<s.substr(i,n-i)<<endl;
				return;
			}
		}
	}
	cout<<"NO"<<endl;
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
