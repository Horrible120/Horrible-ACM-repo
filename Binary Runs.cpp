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
	int n;
	cin>>n;

	ll cnt[30][2][2]={};
	for(int i=0,x;i<n;i++){
		cin>>x;
		for(int j=0;j<30;j++){
			cnt[j][x>>j&1][x>>(j+1)&1]++;
		}
	}

	ll val[30][4][4]={};
	for(int j=0;j<30;j++){
		for(int s1=0;s1<4;s1++){
			for(int s2=0;s2<4;s2++){
				for(int x=0;x<2;x++){
					for(int y=0;y<2;y++){
						if((s1>>x&1)&&!(s2>>y&1)){
							val[j][s1][s2]+=cnt[j][x][y];
						}
					}
				}
			}
		}
	}

	int st[31];
	fill(st,st+30,2);
	st[30]=0;

	int m;
	cin>>m;
	while(m--){
		int type,x;
		cin>>type>>x;
		for(int j=0;j<30;j++){
			int b=x>>j&1;
			if(type==1&&!b) st[j]=0;
			if(type==2&&b) st[j]=3;
			if(type==3&&b) st[j]^=3;
		}

		ll ans=0;
		for(int j=0;j<30;j++) ans+=val[j][st[j]][st[j+1]];
		cout<<ans<<'\n';
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
	}

	cout.flush();
	return 0;
}
