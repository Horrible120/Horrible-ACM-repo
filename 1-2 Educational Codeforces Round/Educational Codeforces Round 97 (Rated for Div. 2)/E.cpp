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
	ll n,k,ans=0;
	cin>>n>>k;
	vector<ll> v(n+2,0),b(k+2,0);
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	for(ll i=1;i<=k;i++)
		cin>>b[i];
	for(ll i=1;i<=n;i++)
		v[i]-=i;
	
	b[0]=0;
	b[k+1]=n+1;
	
	v[0]=-INF;
	v[n+1]=INF;
	
	for(ll i=1;i<=k+1;i++){
		if(v[b[i-1]]>v[b[i]]){
			cout<<-1<<endl;
			return;
		}
		multiset<ll> s;
		for(ll j=b[i-1]+1;j<b[i];j++)
			if(v[j]<v[b[i-1]]||v[j]>v[b[i]])
				continue;
			else if(s.empty()||v[j]>=*s.begin())
				s.insert(v[j]);
			else{
				s.erase(s.upper_bound(v[j]));
				s.insert(v[j]);
			}
		ans+=b[i]-b[i-1]-1-s.size();
//		cout<<b[i-1]<<' '<<b[i]<<' '<<s.size()<<endl;
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
