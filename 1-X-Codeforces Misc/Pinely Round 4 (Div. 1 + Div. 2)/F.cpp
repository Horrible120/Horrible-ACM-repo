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
	ll n,q;
	cin>>n>>q;
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	while(q--){
		ll l,r;
		cin>>l>>r;
		if(r-l>=50)
			cout<<"YES\n";
		else{
			vector<ll> tmp(v.begin()+l,v.begin()+r+1);
			sort(tmp.begin(),tmp.end());
			ll len=r-l+1,flag=1,lst=-1;
			
			for(ll i=0;i<len-2&&flag;i++){
				if(tmp[i]>tmp[i+2]-tmp[i+1]){
					if(lst==-1)
						lst=i;
					else if(i>lst+2)
						flag=0;
				}
			}
			
			for(ll i=0;i<len-5&&flag;i++){
				if( (tmp[i]>tmp[i+2]-tmp[i+1]&&tmp[i+3]>tmp[i+5]-tmp[i+4])||
					(tmp[i]>tmp[i+3]-tmp[i+1]&&tmp[i+2]>tmp[i+5]-tmp[i+4])||
					(tmp[i]>tmp[i+4]-tmp[i+1]&&tmp[i+2]>tmp[i+5]-tmp[i+3])||
					(tmp[i]>tmp[i+5]-tmp[i+1]&&tmp[i+2]>tmp[i+4]-tmp[i+3])||
					
					(tmp[i]>tmp[i+3]-tmp[i+2]&&tmp[i+1]>tmp[i+5]-tmp[i+4])||
					(tmp[i]>tmp[i+4]-tmp[i+2]&&tmp[i+1]>tmp[i+5]-tmp[i+3])||
					(tmp[i]>tmp[i+5]-tmp[i+2]&&tmp[i+1]>tmp[i+4]-tmp[i+3])||
					
					(tmp[i]>tmp[i+4]-tmp[i+3]&&tmp[i+1]>tmp[i+5]-tmp[i+2])||
					(tmp[i]>tmp[i+5]-tmp[i+3]&&tmp[i+1]>tmp[i+4]-tmp[i+2])||
					
					(tmp[i]>tmp[i+5]-tmp[i+4]&&tmp[i+1]>tmp[i+3]-tmp[i+2]) ) flag=0;
			}
			if(flag)
				cout<<"NO\n";
			else
				cout<<"YES\n";
		}
	}
	
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
