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
	ll n,x,y;
	cin>>n>>x>>y;
	if(n%2==0){
		if(x%2!=y%2)
			for(ll i=1;i<=n;i++)
				cout<<i%2<<" \n"[i==n];
		else{
			for(ll i=1;i<=n;i++)
				if(i==x) cout<<2<<' ';
				else if(i%2==x%2) cout<<0<<' ';
				else cout<<1<<' ';
			cout<<endl;
		}	
	}
	else{
		vector<ll> v(n+1);
//		for(ll i=1;i<=n-1;i++)
//			v[i]=i%2;
//		v[n]=2;
		for(ll i=1;i<=n;i++){
			if(i<x) cout<<i%2<<' ';
			if(i==x) cout<<2<<' ';
			if(i>x) cout<<(i+1)%2<<' ';
		}
		cout<<endl;
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
