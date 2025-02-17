#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

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
ll dp[2][301][301][4];	//[][a][b][lst]
ll ans[302][302][302];	//[a][b][c]

void solve(){
	ll n,q,cnt=0;
	cin>>n>>q;
	string s;
	cin>>s;
	vector<ll> v(n+1);
	for(ll i=1;i<=n;i++){
		if(s[i-1]=='?') continue;
		v[i]=s[i-1]-'a'+1;
	}
	
//	for(ll i=1;i<=n;i++) cout<<v[i]<<' '; cout<<endl;
	
	if(v[1]!=0){
		dp[1][0][0][v[1]]=1;
	}
	else{
		cnt++;
		dp[1][1][0][1]=1;
		dp[1][0][1][2]=1;
		dp[1][0][0][3]=1;
	}
	
	for(ll i=2;i<=n;i++){
		ll cur=i%2,lst=(i+1)%2;
		if(v[i]==0) cnt++;	//到目前为止需要几件衣服
		
		for(ll j=0;j<=cnt;j++)	//初始化当前层
			for(ll k=0;k+j<=cnt;k++)
				for(ll col=1;col<=3;col++)
					dp[cur][j][k][col]=0;
		
		for(ll j=0;j<=cnt;j++)	//转移
			for(ll k=0;k+j<=cnt;k++){
				if(v[i]!=0){
					if(v[i]==1) dp[cur][j][k][1]+=dp[lst][j][k][2]+dp[lst][j][k][3];
					else if(v[i]==2) dp[cur][j][k][2]+=dp[lst][j][k][1]+dp[lst][j][k][3];
					else if(v[i]==3) dp[cur][j][k][3]+=dp[lst][j][k][2]+dp[lst][j][k][1];
					
					dp[cur][j][k][v[i]]%=Mod;
					/*cout<<"!!!"<<dp[cur][j][k][v[i]]<<endl;*/
				}
				else{
					if(j>0) dp[cur][j][k][1]+=dp[lst][j-1][k][2]+dp[lst][j-1][k][3];
					if(k>0) dp[cur][j][k][2]+=dp[lst][j][k-1][1]+dp[lst][j][k-1][3];
					dp[cur][j][k][3]+=dp[lst][j][k][2]+dp[lst][j][k][1];
					
					dp[cur][j][k][1]%=Mod;
					dp[cur][j][k][2]%=Mod;
					dp[cur][j][k][3]%=Mod;
				}
			}
	}
	ll i=n%2;
	for(ll j=0;j<=cnt;j++)	//转移到计数dp
		for(ll k=0;k+j<=cnt;k++){
			for(ll col=1;col<=3;col++)
				ans[j+1][k+1][cnt-j-k+1]+=dp[i][j][k][col]/*,cout<<"!!!"<<j<<' '<<k<<' '<<cnt-j-k<<' '<<dp[i][j][k][col]<<endl*/;
			ans[j+1][k+1][cnt-j-k+1]%=Mod;
		}
//	cout<<"!!!"<<endl;
	for(ll i=1;i<=301;i++)
		for(ll j=1;j<=301;j++)
			for(ll k=1;k<=301;k++){
				ans[i][j][k]=(ans[i-1][j][k]+ans[i][j-1][k]+ans[i][j][k-1]-
					ans[i-1][j-1][k]-ans[i-1][j][k-1]-ans[i][j-1][k-1]+
					ans[i-1][j-1][k-1]+ans[i][j][k]+10*Mod)%Mod;
				
			}
	for(ll i=1;i<=q;i++){
		ll a,b,c;
		cin>>a>>b>>c;
//		OOO
		cout<<(ans[a+1][b+1][c+1])%Mod<<endl;
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
