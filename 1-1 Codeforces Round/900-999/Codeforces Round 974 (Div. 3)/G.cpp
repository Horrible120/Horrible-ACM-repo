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
	ll n,m,k,ans=0;
	cin>>n>>m>>k;
	vector<ll> a(n+2,0),d(n+2,0);
	
	set<pll,greater<pll>> mk;
	
	for(ll i=1;i<=n;i++)
		cin>>d[i]>>a[i];
	d[n+1]=1e9,a[n+1]=0;
	
	vector<pll> stk(2*n+1);
	
	ll now=d[1],top=0;
	for(ll i=1;i<=n;i++){
		stk[++top]=make_pair(d[i],a[i]);
		
		ll date=d[i],res=0;
		while(top){
			auto &[dt,vl]=stk[top--];
			if(dt+k-1<date)
				continue;
			else if(date==d[i+1])
				break;
			else{
				if(dt+k>=d[i+1]&&date+(res+vl)/m>=d[i+1]){
					ans+=d[i+1]-date;
					stk[++top]=make_pair(dt,vl+res-(d[i+1]-date)*m);
					break;
				}
				if(dt+k<=date+(res+vl)/m-1){
					ans+=dt+k-date;
					date=dt+k;
					res=0;
				}
				else{
					ans+=(res+vl)/m;
					date+=(res+vl)/m;
					res=(res+vl)%m;
				}
			}
		}
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
