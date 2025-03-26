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

class H_Dsu{
public:
	ll n,m;
	
	class Info{
	public:
		ll fax,fay,siz;
		// $$$ 其他信息自行添加
		ll xx,xn,yx,yn;
		
		Info()=default;	//无效Info初始化
		
		Info(ll _fax,ll _fay):fax(_fax),fay(_fay){
			siz=1;
			xx=xn=fax;
			yx=yn=fay;
		}	//有效初始化
		
		friend Info operator+(const Info &a,const Info &b){
			Info res;
			// $$$ Info合并(只可对集合的根节点操作)
			res.fay=a.fay;
			res.fax=a.fax;	//父亲不变
			
			res.siz=a.siz+b.siz;
			
			res.xx=max(a.xx,b.xx);
			res.xn=min(a.xn,b.xn);
			
			res.yx=max(a.yx,b.yx);
			res.yn=min(a.yn,b.yn);
			
			return res;
		}
	};
	
	v2ct<Info> v;
	
	H_Dsu(ll _n,ll _m):n(_n),m(_m){
		v.assign(n+1,vector<Info>(m+1,Info()));
		for(ll i=1;i<=n;i++)
			for(ll j=1;j<=m;j++)
				v[i][j]=Info(i,j);
	}
	
	pair<ll,ll> Fa(ll x,ll y){
		if(v[x][y].fax==x&&v[x][y].fay==y) return make_pair(x,y);
		auto [x1,y1]=Fa(v[x][y].fax,v[x][y].fay);
		v[x][y].fax=x1;
		v[x][y].fay=y1;
		return make_pair(x1,y1);
	}
	
	void merge(ll x1,ll y1,ll x2,ll y2){ //y向x合并
		pair<ll,ll> fx=Fa(x1,y1),fy=Fa(x2,y2);
		if(fx==fy) return;
		if(v[fx.first][fx.second].siz<v[fy.first][fy.second].siz)
			swap(fx,fy);
		v[fy.first][fy.second].fax=fx.first;
		v[fy.first][fy.second].fay=fx.second;
		v[fx.first][fx.second]=v[fx.first][fx.second]+v[fy.first][fy.second];
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	v2ct<ll> v(n+1,vector<ll>(m+1));
	for(ll i=1;i<=n;i++){
		string s;
		cin>>s;
		for(ll j=1;j<=m;j++)
			v[i][j]=(s[j-1]=='#'?1:0);
	}
	v2ct<ll> dif(n+2,vector<ll>(m+2,0));
	v2ct<ll> d(n+1,vector<ll>(m+1,0));
	H_Dsu dsu=H_Dsu(n,m);
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++)if(v[i][j]){
			if(v[i-1][j])
				dsu.merge(i,j,i-1,j);
			if(v[i][j-1])
				dsu.merge(i,j,i,j-1);
		}
	}
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			if(v[i][j]){
				dif[1][j]--;
				dif[1][j+1]++;
				dif[i][1]--;
				dif[i+1][1]++;
				
				auto [x1,y1]=dsu.Fa(i,j);
//				cout<<"!!! "<<i<<' '<<j<<' '<<x1<<' '<<y1<<endl;
				auto it=dsu.v[x1][y1];
				
				it.yn=max(1ll,it.yn-1);
				it.xn=max(1ll,it.xn-1);
				it.yx=min(m,it.yx+1);
				it.xx=min(n,it.xx+1);
				
				dif[1][it.yn]++;
				dif[1][it.yx+1]--;
				dif[it.xn][1]++;
				dif[it.xx+1][1]--;
				
				dif[it.xn][it.yn]--;
				dif[it.xn][it.yx+1]++;
				dif[it.xx+1][it.yn]++;
				dif[it.xx+1][it.yx+1]--;
			}
		}
	}
	
	ll ans=0;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			
			d[i][j]=d[i-1][j]+d[i][j-1]-d[i-1][j-1]+dif[i][j];
			
//			cout<<i<<' '<<j<<' '<<n+m-1+v[i][j]+d[i][j]<<endl;
			
			ans=max(ans,n+m-1+v[i][j]+d[i][j]);
		}
	}
//	OOO
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
