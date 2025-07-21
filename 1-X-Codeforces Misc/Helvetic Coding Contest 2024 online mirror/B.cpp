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
	ll n,cnt=0;
	cin>>n;
	vector<ll> a(n+1,0),vis(n+1,0),ans(n+1,0),wiz(n+1,0);;
	vector<pll> pa(n+1);
	vector<ll> dis(n+1,0);
	
	dis[1]=1;
	dis[2]=0;
	for(ll i=3;i<=n;i++)
		dis[i]=i-1;
	
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		
		if(!vis[a[i]]) cnt++;
		vis[a[i]]++;
		pa[i]=make_pair(a[i],i);
	}
	
	map<ll,ll> col;
	
	if(cnt==n&&vis[0]==0){
		if(n==2){
			cout<<"NO"<<endl;
			return;
		}
		cout<<"YES"<<endl;
		
		for(ll i=1;i<=n;i++){
			if(pa[i].first==3)
				swap(pa[i],pa[1]);
			if(pa[i].first==1)
				swap(pa[i],pa[2]);
			if(pa[i].first==2)
				swap(pa[i],pa[3]);
		}
		
		ans[pa[1].second]=pa[3].second;
		ans[pa[2].second]=pa[1].second;
		ans[pa[3].second]=pa[2].second;
		col[1]=1;
		col[2]=1;
		col[3]=2;
		
		for(ll i=4;i<=n;i++){
			auto [x,j]=pa[i];
			if(x<i){
				col[i]=col[i-x];
				ans[j]=pa[i-x].second;
			}
			else{
				col[i]=x-i+2;
				ans[j]=pa[1].second;
			}
		}
		
		for(ll i=1;i<=n;i++)
			wiz[pa[i].second]=i;
		
		for(ll i=1;i<=n;i++)
			cout<<wiz[i]<<' '<<col[wiz[i]]<<endl;
		
		for(ll i=1;i<=n;i++)
			cout<<ans[i]<<' ';
		cout<<endl;
	}
	else if(vis[0]>0){
		cout<<"YES"<<endl;
		for(ll i=1;i<=n;i++){
			if(pa[i].first==0)
				swap(pa[i],pa[1]);
		}
		ans[pa[1].second]=pa[1].second;
		col[1]=1;
		for(ll i=2;i<=n;i++){
			auto [x,j]=pa[i];
//			cout<<"!!! "<<x<<' '<<i<<' '<<i-x<<endl;
			if(x==0){
				col[i]=1;
				ans[j]=j;
			}
			else if(x<i){
				col[i]=col[i-x];
				
				ans[j]=pa[i-x].second;
			}
			else{
				col[i]=x-i+2;
				ans[j]=pa[1].second;
			}
		}
		for(ll i=1;i<=n;i++)
			wiz[pa[i].second]=i;
		
		for(ll i=1;i<=n;i++)
			cout<<wiz[i]<<' '<<col[wiz[i]]<<endl;
		
		for(ll i=1;i<=n;i++)
			cout<<ans[i]<<' ';
		cout<<endl;
	}
	else{
		cout<<"YES"<<endl;
		ll bb=0,cnt=0;
		for(ll i=1;i<=n&&bb==0;i++)
			if(vis[i]>1)
				bb=i;
		
		for(ll i=1;i<=n;i++){
			if(pa[i].first==bb&&cnt==0)
				swap(pa[i],pa[1]),cnt++;
			else if(pa[i].first==bb&&cnt==1)
				swap(pa[i],pa[2]),cnt++;
		}
		
		ans[pa[1].second]=pa[2].second;
		col[1]=1;
		ans[pa[2].second]=pa[1].second;
		col[2]=bb;
		
		for(ll i=3;i<=n;i++){
			auto [x,j]=pa[i];
			if(x==0){
				col[i]=1;
				ans[j]=j;
			}
			else if(x<i){
				col[i]=col[i-x];
				ans[j]=pa[i-x].second;
			}
			else{
				col[i]=x-i+2;
				ans[j]=pa[1].second;
			}
		}
		for(ll i=1;i<=n;i++)
			wiz[pa[i].second]=i;
		
		for(ll i=1;i<=n;i++)
			cout<<wiz[i]<<' '<<col[wiz[i]]<<endl;
		
		for(ll i=1;i<=n;i++)
			cout<<ans[i]<<' ';
		cout<<endl;
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
