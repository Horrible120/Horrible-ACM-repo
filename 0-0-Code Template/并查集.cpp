#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

class H_Dsu{
public:
	ll n;
	
	class Info{
	public:
		ll fa,siz;
		// $$$ 其他信息自行添加
		
		Info()=default;	//无效Info初始化
		
		Info(ll _fa):fa(_fa){}	//有效初始化
		
		friend Info operator+(const Info &a,const Info &b){
			Info res;
			// $$$ Info合并(只可对集合的根节点操作)
			res.fa=a.fa;	//父亲不变
			res.siz=a.siz+b.siz;
			
			return res;
		}
	};
	
	vector<Info> v;
	
	H_Dsu(ll _n):n(_n){
		v.assign(n+1,Info());
		for(ll i=1;i<=n;i++)
			v[i].fa=i;
	}
	
	ll Fa(ll x){
		if(v[x].fa==x) return x;
		return v[x].fa=Fa(v[x].fa);
	}
	
	void merge(ll x,ll y){ //y向x合并
		ll fx=Fa(x),fy=Fa(y);
		if(fx==fy) return;
		if(v[fx].siz<v[fy].siz)
			swap(fx,fy);
		v[fy].fa=fx;
		v[fx]=v[fx]+v[fy];
	}
	
};

void solve(){
	
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
