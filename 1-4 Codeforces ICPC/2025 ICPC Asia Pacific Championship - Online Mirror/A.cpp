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

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll r,c,ans=0;
	cin>>r>>c;
	v2ct<ll> mp(r+1,vector<ll>(c+1));
	vector<ll> rsum(r+1),csum(c+1),rrsum(r+1),ccsum(c+1),crrsum(c+1),rccsum(r+1),rcsum(r+1),crsum(c+1),rcrsum(r+1),crcsum(c+1);
	for(ll i=1;i<=r;i++){
		string s;
		cin>>s;
		for(ll j=1;j<=c;j++){
			mp[i][j]=(s[j-1]=='#'?0:1);
			rsum[i]+=mp[i][j];
			csum[j]+=mp[i][j];
		}
	}
	for(ll i=1;i<=r;i++)
		for(ll j=1;j<=c;j++)
			if(mp[i][j]){
				rcsum[i]+=csum[j];
				ccsum[j]+=csum[j];
				crsum[j]+=rsum[i];
				rrsum[i]+=rsum[i];
			}
	
	for(ll i=1;i<=r;i++)
		cout<<i<<' '<<rcsum[i]<<endl;
	
	for(ll i=1;i<=r;i++)
		for(ll j=1;j<=c;j++)
			if(mp[i][j]){
				rcrsum[i]+=crsum[j];
				crcsum[j]+=rcsum[i];
				crrsum[j]+=rrsum[i];
				rccsum[i]+=ccsum[j];
			}
	for(ll i=1;i<=r;i++)
		for(ll j=1;j<=c;j++)
			if(mp[i][j]){
				ans+=rcrsum[i]-rcsum[i]+2*rsum[i]-rrsum[i]-crsum[j]+csum[j]-1;
				ans+=crcsum[j]-crsum[j]+2*csum[j]-ccsum[j]-rcsum[i]+rsum[i]-1;
				ans+=(crrsum[j]-2*crsum[j]+csum[j]-rrsum[i]+2*rsum[i]-1);
				ans+=(rccsum[i]-2*rcsum[i]+rsum[i]-ccsum[j]+2*csum[j]-1);
				
			}
	
	OOO
	cout<<ans<<endl;
	
	for(ll i=1;i<=r;i++)
		if(rsum[i]>=4)
			ans+=rsum[i]*(rsum[i]-1)*(rsum[i]-2)*(rsum[i]-3);
	for(ll i=1;i<=c;i++)
		if(csum[i]>=4)
			ans+=csum[i]*(csum[i]-1)*(csum[i]-2)*(csum[i]-3);
	OOO
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
