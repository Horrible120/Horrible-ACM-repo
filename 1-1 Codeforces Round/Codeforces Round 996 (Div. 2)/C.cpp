#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,m,st=0;
	cin>>n>>m;
	v2ct<ll> mp(n+1,vector<ll>(m+1,0)),mp2(n+1,vector<ll>(m+1,0));
	string s;
	cin>>s;
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			cin>>mp[i][j];
	
	mp2[1][1]=0;
	ll cx=1,cy=1;
	for(ll i=1;i<=n+m-2;i++){
		char ch;
		ch=s[i-1];
		
		if(i==1){
			if(ch=='D')
				for(ll i=1;i<=m;i++)
					st+=mp[1][i];
			else
				for(ll i=1;i<=n;i++)
					st+=mp[i][1];
		}
		
		if(ch=='D'){
			ll cur=0,cur1=0;
			for(ll i=1;i<=m;i++)
				cur+=mp[cx][i],cur1+=mp2[cx][i];
			mp[cx][cy]=st-cur;
			mp2[cx][cy]=1-cur1;
			cx++;
		}
		else{
			ll cur=0,cur1=0;
			for(ll i=1;i<=n;i++)
				cur+=mp[i][cy],cur1+=mp2[i][cy];
			mp[cx][cy]=st-cur;
			mp2[cx][cy]=1-cur1;
			cy++;
		}
	}
	
	ll x1=0,x2=0,k1=0,k2=0;
	for(ll i=1;i<=m;i++)
		k1+=mp[n][i],x1+=mp2[n][i];
	k1=st-k1,x1=1-x1;
	for(ll i=1;i<=n;i++)
		k1+=mp[i][m],x1+=mp2[i][m];
	k2=st-k2,x2=1-x2;
	ll ansx=(x2==x1?0:(k1-k2)/(x2-x1));
	
	k1=0;
	st+=ansx;
	for(ll i=1;i<=m;i++)
		k1+=mp[n][i]+ansx*mp2[n][i];
	mp[n][m]=st-k1;
	
//	OOO
//	cout<<k1<<' '<<k2<<' '<<x1<<' '<<x2<<endl;
//	cout<<mp2[n][m]<<endl;
	
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			cout<<mp[i][j]+ansx*mp2[i][j]<<" \n"[j==m];
	cout.flush();
	
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
