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
	ll l,n,m;
	cin>>l>>n>>m;
	vector<ll> v(l+3,0),inv(n*m+1,0);
	v2ct<ll> mt(n+1,vector<ll>(m+1,0));
	v2ct<pll> win(l+2);
	
	vector<ll> rk;
	for(ll i=1;i<=l;i++)
		cin>>v[i],
		rk.emplace_back(v[i]);
	sort(rk.begin(),rk.end());
	rk.erase(unique(rk.begin(),rk.end()),rk.end());
	for(ll i=1;i<=l;i++)
		inv[v[i]]=(lower_bound(rk.begin(),rk.end(),v[i])-rk.begin()+1),
		v[i]=inv[v[i]];
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++){
			cin>>mt[i][j];
			mt[i][j]=inv[mt[i][j]];
		}
	
	for(ll i=n;i>=1;i--)
		for(ll j=m;j>=1;j--)
			if(mt[i][j]&&(win[mt[i][j]].empty()||win[mt[i][j]].back().second<j))
				win[mt[i][j]].emplace_back(i,j);
	
	vector<ll> sg(m+2,0),psg(m+2,0);
	
	for(ll x=l;x>=1;x--){
		ll i=v[x];
//		OOO
//		cout<<'['<<i<<','<<v[i]<<']'<<"   ";
//		for(auto [x,y]:win[i])
//			cout<<'('<<x<<','<<y<<')'<<' ';
//		cout<<endl;
		
		ll l=0,r=0;
		for(ll j=0;j<win[i].size();j++){
			
			while(l<win[v[x+1]].size()&&win[v[x+1]][l].second<=win[i][j].second)
				++l;
			while(r<win[v[x+1]].size()&&win[v[x+1]][r].first>win[i][j].first)
				++r;
			//可行区间 [l,r-1]
			if(l<r)
				sg[j+1]=(psg[r]-psg[l]<=0);
			else
				sg[j+1]=1;
				
		}
		psg[0]=sg[0]=0;
		for(ll j=1;j<=win[i].size();j++)
			psg[j]=psg[j-1]+sg[j],sg[j]=0;
	}
//	OOO OOO
	
	if(psg[win[v[1]].size()]>0)
		cout<<'T'<<endl;
	else
		cout<<'N'<<endl;
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
