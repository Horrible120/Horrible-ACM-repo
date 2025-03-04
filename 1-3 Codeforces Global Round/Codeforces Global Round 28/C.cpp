#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	string s;
	cin>>s;
	vector<ll> v(s.size()+2);
	for(ll i=0;i<s.size();i++)
		v[i+1]=s[i]=='1'?1:0;
	
	ll len=0,st=0;
	for(ll i=1;i<=s.size()&&(!len);i++){
		if(v[i]==0){
			while(i+len<=s.size()&&v[i+len]==0) len++;
			st=i;
		}
	}
	if(len==0) cout<<1<<' '<<s.size()<<' '<<1<<' '<<1<<endl;
	else if(st-1>=len) cout<<1<<' '<<s.size()<<' '<<st-len<<' '<<st-len+(s.size()-st+1)-1<<endl;
	else cout<<1<<' '<<s.size()<<' '<<1<<' '<<1+(s.size()-st+1)-1<<endl;
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
