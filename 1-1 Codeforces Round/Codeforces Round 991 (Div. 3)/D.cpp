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

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		string s;
		cin>>s;
		vector<ll> v(s.size()+1);
		for(ll i=0;i<s.size();i++)
			v[i+1]=s[i]-'0';
		ll n=s.size();
		for(ll i=1;i<=n;i++){
			ll mx=i,mt=v[i];
			for(ll j=1;j<=8&&i+j<=n;j++)
				if(v[j+i]-j>mt){
					mx=j+i;
					mt=v[j+i]-j;
				}
					
			if(mx!=i){
				ll tmp=v[mx]-(mx-i);
				for(ll j=mx;j>i;j--)
					v[j]=v[j-1];
				v[i]=tmp;
			}
		}
//		OOO
		for(ll i=1;i<=n;i++)
			cout<<v[i];
		cout<<endl;
	}
	
	cout.flush();
	
	return 0;
}
