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

ll gf(vector<ll> &fa,ll x){
	if(fa[x]==x) return x;
	return fa[x]=gf(fa,fa[x]);
}

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<ll> tar(n+1),pn(n+1);
	string s;
	cin>>s;
	for(ll i=1;i<=n;i++)
		tar[i]=(s[i-1]=='B');
	
	for(ll i=1;i<=n;i++)
		cin>>pn[i];
	
	if(k==0){
		ll mxx=0;
		for(ll i=1;i<=n;i++){
//			cout<<tar[i]<<endl;
			if(tar[i]==1)
				mxx=max(mxx,pn[i]);
		}
		cout<<mxx<<endl;
		return;
	}
	
	vector<pair<ll,ll>> ans;
	ll B=0,cnt=0;
	for(ll i=1;i<=n;i++){
		ll tmp=i,mx=pn[i];
		if(tar[i]==1) B++;
		while(tmp<n&&tar[tmp+1]==tar[i]) tmp++,mx=max(mx,pn[tmp]);
		
//		cout<<mx<<endl;
		i=tmp;
		if((cnt==0&&tar[i]==0)||(tmp==n&&tar[i]==0)) continue;
		ans.emplace_back(mx,++cnt);
	}
	
//	OOO
	if(B<=k){
		cout<<0<<endl;
	}
	else{
		ll l=1,r=1e9;
		while(l<r){
			ll mid=(l+r-1)/2;
			ll flag=0;
			ll ct=0;
			vector<ll> vis(cnt+1,0);
			for(ll i=1;i<=cnt;i++){
				if(vis[i-1]==0&&ans[i-1].first<=mid) ct++,vis[i]=1;
			}
//			cout<<"!!!"<<cnt<<endl;
			if(ct>=B-k) flag=1;
			
			if(flag) r=mid;
			else l=mid+1;
		}
		cout<<l<<endl;
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
/*

5
5 1
RBRBR
9 5 5 3 1
10 0
BRBRBBRRBR
5 1 2 4 5 3 6 1 5 4
*/
