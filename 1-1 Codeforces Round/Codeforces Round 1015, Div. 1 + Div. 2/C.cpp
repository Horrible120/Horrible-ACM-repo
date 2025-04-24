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
	vector<ll> a(n+1,0),b(n+1,0),pa(n+1,0),pb(n+1,0),pos(n+1,0),vis(n+1,0);
	
	for(ll i=1;i<=n;i++)
		cin>>a[i];
	for(ll i=1;i<=n;i++)
		cin>>b[i];
	
	ll md=0,mcnt=0;
	
	for(ll i=1;i<=n;i++){
		pa[a[i]]=b[i];
//		cout<<"!! "<<i<<' '<<pa[a[i]]<<endl;
		pb[b[i]]=a[i];
	}
	
	for(ll i=1;i<=n;i++){
		if(a[i]!=pa[pa[a[i]]]){
			cout<<-1<<endl;
//			cout<<i<<endl;
			return;
		}
		if(a[i]==pa[a[i]]){
			md=a[i];
			mcnt++;
		}
	}
	
	if((n%2==0&&mcnt>0)||(n%2==1&&mcnt!=1)){
		cout<<-1<<endl;
		return;
	}
	
	for(ll i=1;i<=n;i++){
		pos[a[i]]=i;
	}
	ll cnt=0;
	vector<pair<ll,ll>> ans;
	for(ll i=1;i<=n;i++){
		if(i!=md&&vis[i]==0){
			ll ta=pos[i];
			if(ta!=1+cnt)
				ans.emplace_back(ta,1+cnt);
			pos[a[1+cnt]]=pos[i];
			swap(a[1+cnt],a[ta]);
			pos[i]=1+cnt;
			
			ll tb=pos[pa[i]];
			if(tb!=n-cnt)
				ans.emplace_back(tb,n-cnt);
			pos[a[n-cnt]]=pos[pa[i]];
			swap(a[n-cnt],a[tb]);
			pos[pa[i]]=n-cnt;
			
			
			
			
			
			
			
			
			cnt++;
			vis[i]=1;
			vis[pa[i]]=1;
			
		}
	}
//	OOO
	cout<<ans.size()<<endl;
	for(auto [x,y]:ans)
		cout<<x<<' '<<y<<endl;
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
