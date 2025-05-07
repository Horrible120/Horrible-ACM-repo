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
	ll n;
	cin>>n;
	string s;
	cin>>s;
	
	ll t1=0,l1=0,t2=0,l2=0,s1=0,s2=0,ans=0;
	for(ll i=1;i<=n;i++){
		if(s[i-1]=='0'){
			if(i>1){
				s1+=i-1;
				t1=1;
				l1=i-1;
			}
			if(i<n){
				s2+=n-i;
				t2=i+1;
				l2=n;
			}
		}
		else{
			if(t1&&i<=l1){
				s1+=1;
				t1=l1=i;
				s2=l2=t2=0;
			}
			else if(t2&&i>=t2){
				s1=s2+1;
				t1=l1=i;
				s2=l2=t2=0;
			}
			else{
				s1=1;
				l1=t1=i;
				s2=l2=t2=0;
			}
		}
//		OOO
//		cout<<i<<' '<<s1<<' '<<s2<<endl;
		ans=max(ans,s1);
		ans=max(ans,s2);
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
	}
	
	cout.flush();
	return 0;
}
