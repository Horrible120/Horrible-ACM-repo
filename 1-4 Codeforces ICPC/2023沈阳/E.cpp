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
	ll x1,y1,p,q,x2=0,y2=0,ans=0;
	cin>>x1>>y1>>p>>q;
	
	while(x1>0){
		ll tx=0,ty=0;
		for(ll i=0;i<=x1;i++)
			for(ll j=0;j+i<=p&&j<=y1;j++){
				if((i+q>j||i==0)&&((x1-i+q)>=(y1-j)||i==x1)/*&&((x2+i+q)>=(y2+j)||x2+i==0)*/){
					if(i>tx||(i==tx&&j>ty))
						tx=i,ty=j;
				}
			}
		if(tx==0&&ty==0){
			cout<<-1<<endl;
			return;
		}
		else{
			x1-=tx;
			x2+=tx;
			y1-=ty;
			y2+=ty;
			ans++;
		}
		OOO
		cout<<tx<<' '<<ty<<endl;
		
		if(x1==0)
			break;
		
		tx=1000,ty=1000;
		for(ll i=0;i<=x2;i++)
			for(ll j=0;j+i<=p&&j<=y2;j++){
				if((i+q>j||i==0)/*&&((x1+i+q)>=(y1+j)||x1+i==0)*/&&((x2-i+q)>=(y2-j)||i==x2)){
					if(i<tx||(i==tx&&j<ty))
						tx=i,ty=j;
				}
			}
		if(tx==1000&&ty==1000){
			cout<<-1<<endl;
			return;
		}
		else{
			x1+=tx;
			x2-=tx;
			y1+=ty;
			y2-=ty;
			ans++;
		}
		OOO
		cout<<tx<<' '<<ty<<endl;
	}
	
	
	cout<<ans<<endl;
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
