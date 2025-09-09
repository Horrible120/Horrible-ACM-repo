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

ll Map[2002][2002];

void solve(){
	ll n,m,k,ans=0;
	cin>>n>>m>>k;
	string s;
	cin>>s;
	ll len=s.size();
	
	ll x1=1,y1=1,x2=n,y2=m,x3=n,y3=m;
	ll dx1=1,dy1=1,dx2=n,dy2=m;
	vector<pll> pa;
	
	pa.emplace_back(x3,y3);
	Map[x3][y3]=1;
	
	for(ll i=0;i<len;i++){
		if(s[i]=='U'){
			x1--;
			x2--;
			x3++;
			dx1=max(dx1,x1);
			dx2=min(dx2,x2);
		}else if(s[i]=='D'){
			x1++;
			x2++;
			x3--;
			dx1=max(dx1,x1);
			dx2=min(dx2,x2);
		}else if(s[i]=='R'){
			y1++;
			y2++;
			y3--;
			dy1=max(dy1,y1);
			dy2=min(dy2,y2);
		}else{
			y1--;
			y2--;
			y3++;
			dy1=max(dy1,y1);
			dy2=min(dy2,y2);
		}
		
//		cout<<"!! "<<x3<<' '<<y3<<endl;
		
		pa.emplace_back(x3,y3);
		if(x3>=0&&y3>=0&&x3<=2001&&y3<=2001) Map[x3][y3]=1;
	}
	
//	cout<<"!!! ["<<dx1<<','<<dy1<<']'<<' '<<'['<<dx2<<','<<dy2<<']'<<endl;
	
	if(dx1>dx2||dy1>dy2){
		if(k==0){
			cout<<n*m<<endl;
		}else{
			cout<<0<<endl;
		}
		
		for(auto [x,y]:pa){
			if(x>=0&&y>=0&&x<2002&&y<2002) Map[x][y]=0;
		}
		
		return;
	}
	
	vector<vector<ll>> pref(n*2+1,vector<ll>(m*2+1,0));
	
	for(ll i=1;i<=n*2;i++){
		for(ll j=1;j<=m*2;j++){
			pref[i][j]=pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1]+Map[i][j];
//			cout<<pref[i][j]<<' ';
		}
//		cout<<endl;
	}
	
	ll w=dx2-dx1+1;
	ll h=dy2-dy1+1;
	
	ll dx3=n-dx2+1,dy3=m-dy2+1;
//	cout<<"!!! ["<<dx3<<','<<dy3<<']'<<' '<<w<<' '<<h<<endl;
	
	for(ll i=dx3;i<=dx3+n-1;i++){
		for(ll j=dy3;j<=dy3+m-1;j++){
			ll sum=pref[i+w-1][j+h-1]-pref[i+w-1][j-1]-pref[i-1][j+h-1]+pref[i-1][j-1];
			if(w*h-sum==k){
//				cout<<n-(i-dx3)<<' '<<m-(j-dy3)<<endl;
				ans++;
			}
		}
	}
	
	cout<<ans<<endl;

	for(auto [x,y]:pa){
		if(x>=0&&y>=0&&x<2002&&y<2002) Map[x][y]=0;
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
