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

ll dx[4]={0,1,0,-1};
ll dy[4]={1,0,-1,0};

void solve(){
	ll n,m;
	cin>>n>>m;
	
	v2ct<ll> v(n+1,vector<ll>(m+1,0)),vis(n+1,vector<ll>(m+1,0));
	
	for(ll i=1;i<=n;i++){
		string s;
		cin>>s;
		for(ll j=0;j<m;j++){
			v[i][j+1]=(s[j]=='#');
		}
	}
	
	{
		for(ll i=1;i<=n;i++){
			ll mn=INF,mx=0;
			for(ll j=1;j<=m;j++){
				if(v[i][j]){
					mn=min(mn,j);
					mx=max(mx,j);
				}
			}
			
			if(mx>0){
				for(ll j=mn;j<=mx;j++){
					v[i][j]=1;
				}
			}
		}
		
		for(ll i=1;i<=m;i++){
			ll mn=INF,mx=0;
			for(ll j=1;j<=n;j++){
				if(v[j][i]){
					mn=min(mn,j);
					mx=max(mx,j);
				}
			}
			
			if(mx>0){
				for(ll j=mn;j<=mx;j++){
					v[j][i]=1;
				}
			}
		}
		
//		for(ll i=1;i<=n;i++)
//			for(ll j=1;j<=m;j++)
//				cout<<v[i][j]<<" \n"[j==m];
//		cout.flush();
//		
	}
	
	ll cnt=0;
	vector<ll> xmx(4,0),xmn(4,INF),ymx(4,0),ymn(4,INF);
	
	auto DFS=[&](auto &&self,ll x,ll y)->void{
		vis[x][y]=1;
		xmx[cnt]=max(xmx[cnt],x);
		ymx[cnt]=max(ymx[cnt],y);
		xmn[cnt]=min(xmn[cnt],x);
		ymn[cnt]=min(ymn[cnt],y);
		for(ll i=0;i<=3;i++){
			if((x+dx[i]>=1&&x+dx[i]<=n&&y+dy[i]>=1&&y+dy[i]<=m)&&v[x+dx[i]][y+dy[i]]&&!vis[x+dx[i]][y+dy[i]]){
				self(self,x+dx[i],y+dy[i]);
			}
		}
	};
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			if(!vis[i][j]&&v[i][j]){
				++cnt;
				DFS(DFS,i,j);
			}
		}
	}
	
//	cout<<xmx[1]<<' '<<xmx[2]<<endl;
	
	if(cnt>1){
		if(xmx[1]>xmx[2]){
			swap(xmx[1],xmx[2]);
			swap(xmn[1],xmn[2]);
			swap(ymx[1],ymx[2]);
			swap(ymn[1],ymn[2]);
			
		}
		
		{
			if(ymx[1]<ymx[2]){
				for(ll j=ymn[1],flag=0;j<=ymx[1];j++){
					ll i=xmx[1];
					if(v[i][j]) flag=1;
					while(!v[i][j]&&flag) v[i--][j]=1;
				}
				for(ll j=ymx[2],flag=0;j>=ymn[2];j--){
					ll i=xmn[2];
					if(v[i][j]) flag=1;
					while(!v[i][j]&&flag) v[i++][j]=1;
				}
			}else{
				for(ll j=ymx[1],flag=0;j>=ymn[1];j--){
					ll i=xmx[1];
					if(v[i][j]) flag=1;
					while(!v[i][j]&&flag) v[i--][j]=1;
				}
			for(ll j=ymn[2],flag=0;j<=ymx[2];j++){
					ll i=xmn[2];
					if(v[i][j]) flag=1;
					while(!v[i][j]&&flag) v[i++][j]=1;
				}
			}
			
			
			if(ymx[1]<ymx[2]){
				for(ll i=xmx[1];i<=xmn[2];i++) v[i][ymx[1]]=1;
				for(ll i=ymx[1];i<=ymn[2];i++) v[xmn[2]][i]=1;
			}else{
				for(ll i=xmx[1];i<=xmn[2];i++) v[i][ymn[1]]=1;
				for(ll i=ymx[2];i<=ymn[1];i++) v[xmn[2]][i]=1;
			}
			
		}
	}
	
	{
		for(ll i=1;i<=n;i++){
			ll mn=INF,mx=0;
			for(ll j=1;j<=m;j++){
				if(v[i][j]){
					mn=min(mn,j);
					mx=max(mx,j);
				}
			}
			
			if(mx>0){
				for(ll j=mn;j<=mx;j++){
					v[i][j]=1;
				}
			}
		}
		
		for(ll i=1;i<=m;i++){
			ll mn=INF,mx=0;
			for(ll j=1;j<=n;j++){
				if(v[j][i]){
					mn=min(mn,j);
					mx=max(mx,j);
				}
			}
			
			if(mx>0){
				for(ll j=mn;j<=mx;j++){
					v[j][i]=1;
				}
			}
		}
		
//		for(ll i=1;i<=n;i++)
//			for(ll j=1;j<=m;j++)
//				cout<<v[i][j]<<" \n"[j==m];
//		cout.flush();
//		
	}
	
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			cout<<(v[i][j]==1?'#':'.');
		}
		cout<<endl;
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
