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

void solve(){
	ll n,k;
	cin>>n>>k;
	vector<ll> a(n+1,0),ans(n+1,0);
	vector<ll> nxt(n+1,0),vis(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
	}
	
	for(ll i=1;i<=n;i++){
		nxt[a[i]]=i;
	}
	
	ll rcnt=0;
	vector<vector<ll>> ring(1),scnt(n+1);
	vector<ll> siz(1);
	
	for(ll i=1;i<=n;i++){
		if(!vis[i]){
			rcnt++;
			ring.emplace_back(vector<ll>());
			siz.emplace_back(0);
			ll tmp=i;
			while(!vis[tmp]){
				vis[tmp]=1;
				siz.back()++;
				ring.back().emplace_back(tmp);
				tmp=nxt[tmp];
			}
			scnt[siz.back()].emplace_back(rcnt);
		}
	}
	
//	for(auto &r:ring){
//		cout<<">>>> ";
//		for(auto &it:r){
//			cout<<it<<' ';
//		}
//		cout<<endl;
//	}
	
	ll flag=1;
	for(ll i=2;i<=n&&flag;i+=2){
		ll c=scnt[i].size();
		if(__lg(c)>=k&&c%(1<<k)==0){
			if(c==0) continue;
			ll sz=i*(1<<k);
			
			for(ll z=1;z<=(c>>k);z++){
				vector<ll> tmp;
				for(ll j=0;j<i;j++){
					for(ll l=(z-1)*(1<<k);l<z*(1<<k);l++){
						tmp.emplace_back(ring[scnt[i][l]][j]);
					}
				}
//				cout<<"! "<<sz<<endl;
//				for(auto it:tmp) cout<<it<<' ';
//				cout<<endl;
				for(ll j=0;j<sz;j++){
					ans[tmp[(j+1)%sz]]=tmp[j];
				}
			}
			
		}else if(c){
			flag=0;
		}
	}
	
	for(ll i=1;i<=n;i+=2){
		ll c=scnt[i].size();
		for(ll len=1<<min(20ll,k);len>0&&c>0;len>>=1){
			while(c>=len){
				{
					ll rd=k-__lg(len);
					ll cc=(i+1)/2,gap=1,tp=1;
					while(rd>0){
						if(rd&tp){
							rd^=tp;
							gap=gap*cc%i;
						}
						cc=cc*cc%i;
						tp*=2;
					}
					vector<ll> tmp(i,0);
					for(ll l=c-len;l<c;l++){
						for(ll j=0;j<i;j++){
							tmp[j]=ring[scnt[i][l]][j*gap%i];
						}
						ring[scnt[i][l]]=tmp;
					}
				}
				
				{
					vector<ll> tmp;
					for(ll j=0;j<i;j++){
						for(ll l=c-len;l<c;l++){
							tmp.emplace_back(ring[scnt[i][l]][j]);
						}
					}
					for(ll j=0;j<i*len;j++){
						ans[tmp[(j+1)%(i*len)]]=tmp[j];
					}
				}
				c-=len;
			}
		}
	}
	
//	OOO
	if(!flag){
		cout<<"NO"<<endl;
	}else{
		cout<<"YES"<<endl;
		for(ll i=1;i<=n;i++){
			cout<<ans[i]<<' ';
		}
		cout<<endl;
	}
	
	
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cout<<__lg(2)<<endl;
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
