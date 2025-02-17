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

void solve(){
	ll t,a1,a2,a3,a4;
	cin>>t>>a1>>a2>>a3>>a4;
	v2ct<ll> e(16,vector<ll>(16,INF)),dis(16,vector<ll>(16,INF));
	v2ct<ll> f((1<<16)+1,vector<ll>(16,INF));
	
	auto adeg=[&](ll u,ll v,ll w){
		dis[u][v]=w;
		dis[v][u]=w;
	};
	for(ll i=0;i<16;i++){
		dis[i][i]=0;
		adeg(i,i,0);
		adeg(i,i^8,a1);
		adeg(i,i^4,a1);
		adeg(i,i^2,a1);
		adeg(i,i^1,a1);
		adeg(i,i^12,a2);
		adeg(i,i^3,a2);
		adeg(i,i^10,a3);
		adeg(i,i^5,a3);
		adeg(i,i^15,a4);
	}
	for(ll i=0;i<16;i++)
		for(ll j=0;j<16;j++)
			for(ll k=0;k<16;k++)
				dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
	
//	cout<<dis[0][6]<<endl;
	
	for(ll i=0;i<16;i++)
		f[1<<i][i]=dis[0][i];
	f[1][0]=2*min(min(a1,a2),min(a3,a4));
	
	for(ll i=2;i<=16;i++)
		for(ll j=1;j<=(1<<16)-1;j++)
			if(__builtin_popcount(j)==i)
				for(ll p=0;p<16;p++)
					if((j>>p)&1)
						for(ll k=0;k<16;k++)
							if(k!=p)
								f[j][p]=min(f[j][p],f[j^(1<<p)][k]+dis[k][p]);
	
	for(ll i=1;i<=t;i++){
		ll m,pos=0;
		cin>>m;
		for(ll j=1;j<=m;j++){
			string s1,s2;
			cin>>s1>>s2;
//			cout<<(1<<((s1[0]-'0')*8+(s1[1]-'0')*4+(s2[0]-'0')*2+(s2[1]-'0')))<<endl;
			pos+=(1<<(15-((s1[0]-'0')*8+(s1[1]-'0')*4+(s2[0]-'0')*2+(s2[1]-'0'))));
		}
//		cout<<pos<<endl;
		ll ans=INF;
		for(ll j=0;j<16;j++)
			ans=min(ans,f[pos][j]);
//		OOO
		cout<<ans<<endl;
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
