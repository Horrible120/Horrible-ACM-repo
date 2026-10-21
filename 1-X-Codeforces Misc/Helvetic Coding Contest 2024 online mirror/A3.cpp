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
	string s;
	cin>>s;
	ll n=s.size();
	vector<ll> v(n+1,0),top(n+1,0);
	vector<vector<ll>> stk(n+1,vector<ll>(1,0));
	
	ll cur=0,cnt=0,num=0;
	
	for(ll i=0;i<n;i++){
		if(s[i]=='('){
			cnt++;
		}else{
			cur--;
			if(cur<0){
				num++;
				cur=cnt-1;
				cnt=0;
			}
		}
		
//		cout<<i<<' '<<cur<<' '<<cnt<<' '<<num<<endl;
		
		stk[num].emplace_back(s[i]=='('?1:0);
		++top[num];
	}
	
//	OOO
	
//	for(ll i=0;i<=n;i++) cout<<i<<' '<<top[i]<<endl;
	
	string ans="";
	
	ll pref=0;
	for(ll i=1;i<=n;i++){
//		cout<<pref<<' '<<top[pref]<<endl;
		if(stk[pref][top[pref]--]){
			ans+='(';
			pref++;
		}else{
			ans+=')';
			pref--;
		}
		
	}
//	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
