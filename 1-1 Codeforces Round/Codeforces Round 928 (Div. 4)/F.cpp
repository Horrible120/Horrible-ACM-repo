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
	v2ct<ll> mp(8,vector<ll>(8,0));
	for(ll i=0;i<7;i++){
		string s;
		cin>>s;
		for(ll j=0;j<7;j++)
			if(s[j]=='B')
				mp[i][j]=1;
	}
	
	auto check=[&](v2ct<ll> &p,ll k)->bool{
		for(ll i=1;i<6;i++)
			for(ll j=1;j<6;j++)
				if(((i+j)%2)==k&&p[i][j]&&p[i+1][j+1]&&p[i-1][j-1]&&p[i+1][j-1]&&p[i-1][j+1])
					return false;
		return true;
	};
	
	auto tmp=mp;
	ll ans0=INF,ans1=INF;
	
	if(check(tmp,0))
		ans0=0;
	if(check(tmp,1))
		ans1=0;
	
	//考虑偶数
	for(ll x1=0;x1<7;x1++)
		for(ll y1=0;y1<7;y1++)if((x1+y1)%2==0)if(tmp[x1][y1]){
			tmp[x1][y1]=0;
			
			if(check(tmp,0)){
				ans0=min(ans0,1ll);
				tmp[x1][y1]=1;
				continue;
			}
			
			for(ll x2=0;x2<7;x2++)
				for(ll y2=0;y2<7;y2++)if((x2+y2)%2==0)if(tmp[x2][y2]){
					tmp[x2][y2]=0;
					
					if(check(tmp,0)){
						ans0=min(ans0,2ll);
						tmp[x2][y2]=1;
						continue;
					}
					
					for(ll x3=0;x3<7;x3++)
						for(ll y3=0;y3<7;y3++)if((x3+y3)%2==0)if(tmp[x3][y3]){
							tmp[x3][y3]=0;
							
							if(check(tmp,0)){
								ans0=min(ans0,3ll);
								tmp[x3][y3]=1;
								continue;
							}
							
							tmp[x3][y3]=1;
						}
					tmp[x2][y2]=1;
				}
			tmp[x1][y1]=1;
		}
	
	for(ll x1=0;x1<7;x1++)
		for(ll y1=0;y1<7;y1++)if((x1+y1)&1)if(tmp[x1][y1]){
			tmp[x1][y1]=0;
			
			if(check(tmp,1)){
				ans1=min(ans1,1ll);
				tmp[x1][y1]=1;
				continue;
			}
			
			for(ll x2=0;x2<7;x2++)
				for(ll y2=0;y2<7;y2++)if((x2+y2)&1)if(tmp[x2][y2]){
					tmp[x2][y2]=0;
					
					if(check(tmp,1)){
						ans1=min(ans1,2ll);
						tmp[x2][y2]=1;
						continue;
					}
					
					for(ll x3=0;x3<7;x3++)
						for(ll y3=0;y3<7;y3++)if((x3+y3)&1)if(tmp[x3][y3]){
							tmp[x3][y3]=0;
							
							if(check(tmp,1)){
								ans1=min(ans1,3ll);
								tmp[x3][y3]=1;
								continue;
							}
							
							tmp[x3][y3]=1;
						}
					tmp[x2][y2]=1;
				}
			tmp[x1][y1]=1;
		}
	if(ans0>=INF) ans0=4;
	if(ans1>=INF) ans1=4;
	
//	OOO
	cout<<ans0+ans1<<endl;
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
