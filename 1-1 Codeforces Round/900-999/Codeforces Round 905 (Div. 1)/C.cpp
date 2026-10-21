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
	ll n,q,lst=0;
	cin>>n;
	vector<ll> ans(n+2,0),v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		ans[i]=v[i]-v[i-1];
	}
	
	cin>>q;
	vector l(q+1,0),r(q+1,0),x(q+1,0);

	set<ll> pos;
	vector<ll> tr(n+3,0);
	
	for(ll i=1;i<=q;i++){
		cin>>l[i]>>r[i]>>x[i];
		tr[l[i]]+=x[i];
		tr[r[i]+1]-=x[i];
		
		if(tr[l[i]]==0){
			pos.erase(l[i]);
		}else{
			pos.insert(l[i]);
		}
		
		if(tr[r[i]+1]==0){
			pos.erase(r[i]+1);
		}else{
			pos.insert(r[i]+1);
		}
		
		if(pos.size()){
			ll p=*pos.begin();
			if(tr[p]<0){
				lst=i;
				while(pos.size()){
					ll tmp=*pos.begin();
					tr[tmp]=0;
					pos.erase(pos.begin());
				}
			}
		}
	}
	
	for(ll i=1;i<=lst;i++){
		ans[l[i]]+=x[i];
		ans[r[i]+1]-=x[i];
	}
	
//	OOO
	
	for(ll i=1;i<=n;i++){
		ans[i]+=ans[i-1];
		cout<<ans[i]<<" \n"[i==n];
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
		cout.flush();
	}
	
	
	return 0;
}
