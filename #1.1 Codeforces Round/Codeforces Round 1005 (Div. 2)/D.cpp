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
	ll n,q;
	cin>>n>>q;
	vector<ll> w(n+2),hg(n+1),xum(n+2);
	for(ll i=1;i<=n;i++) cin>>w[i];
	for(ll i=1;i<=n;i++) hg[i]=__lg(w[i])+1;
	for(ll i=n;i>=1;i--) xum[i]=xum[i+1]^w[i];
	
	v2ct<ll> nxt(31,vector<ll>(n+2));	//包括自己的下一个第i位上是1 
	
	for(ll i=1;i<=30;i++){
		for(ll j=1;j<=n+1;j++){
			if((w[j]>>(i-1))&1) nxt[i][j]=j;
			else nxt[i][j]=nxt[i][j-1];
		}
//		cout<<i<<' '<<nxt[i][n+1]<<endl;
	}
	
	
	
	for(ll i=1;i<=q;i++){
		ll x,ans=0,cur=n+1;
		cin>>x;
		ll clg=__lg(x)+1;
		for(ll j=clg+1;j<=30;j++)
			ans=max(ans,nxt[j][n+1]);
//		cout<<clg<<' '<<ans<<endl;
		while(clg>0&&cur>0){
//			cout<<"!!!"<<endl;
			if(nxt[clg][cur-1]==0){
				cur=1;
//				cout<<"!!!"<<endl;
				break;
			}
			else{
				if((x^xum[nxt[clg][cur-1]+1])<w[nxt[clg][cur-1]]){
					cur=nxt[clg][cur-1]+1;
					break;
				}
				else{
					ll tmp=x^xum[nxt[clg][cur-1]];
					if(tmp==0){
						cur=nxt[clg][cur-1];
						break;
					}
					for(ll j=__lg(tmp)+2;j<=clg;j++)
						ans=max(ans,nxt[j][nxt[clg][cur-1]-1]);
					cur=nxt[clg][cur-1];
					clg=__lg(tmp)+1;
				}
			}
		}
//		OOO
		cout/*<<ans<<' '<<cur<<' '*/<<min(n-ans,n+1-cur)<<endl;
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
