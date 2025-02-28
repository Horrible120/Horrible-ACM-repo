#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,x,k;
	cin>>n>>x>>k;
	string s;
	cin>>s;
	
	ll p1=min(n,k),flag=0;
	for(ll i=1;i<=p1;i++){
		if(s[i-1]=='L') x--;
		else x++;
		if(x==0){
			flag=i;
			break;
		}
	}
//	cout<<"!!! "<<flag<<endl;
//	OOO
	if(!flag){
		cout<<0<<endl;
	}
	else{
		ll p2=p1-flag;
		x=0;
		ll cr=0;
		for(ll i=1;i<=n;i++){
			if(s[i-1]=='L') x--;
			else x++;
			if(x==0){
				cr=i;
				break;
			}
		}
//		cout<<"!!! "<<cr<<endl;
		if(cr==0)
			cout<<1<<endl;
		else
			cout<<1+(k-flag)/cr<<endl;
	}
	
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
