#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef int ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

template<typename T>
class H_Fenwick{	//树状数组 类
public:
	ll n;	//总的元素个数
	vector<T> val;	//储存树状数组的数据
	
	H_Fenwick(ll _n):n(_n){	// n 个元素的初始化
		val.assign(n+1,0);
	}
	
	ll lb(ll x) {return x&-x;}	//求 lowbit
	
	T query_Prefsum(ll x){	//求前缀和
		T res=0;
		while(x){
			res+=val[x];
			x-=lb(x);
		}
		return res;
	}
	
	T query_Rangesum(ll l,ll r){	//用前缀和求区间和
		return query_Prefsum(r)-query_Prefsum(l-1);
	}
	
	void val_add(ll pos,T key){	//单点修改: 加上key
		while(pos<=n){
			val[pos]+=key;
			pos+=lb(pos);
		}
	}
	
	void val_modify(ll pos,T key){
		val_add(pos,key-query_Rangesum(pos,pos));	//单点修改: 改为key
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<pair<ll,ll>> v(n+1);
	
	struct Ask{
		ll x,y,c,p;
	};
	
	vector<Ask> q;

	vector<ll> ans(m+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i].first>>v[i].second;
		v[i].first++,v[i].second++;	//偏置以避免 0 坐标
	}
	
	for(ll i=1;i<=m;i++){
		ll x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		x1++,y1++,x2++,y2++;	//偏置以避免 0 坐标
		
		//分解矩阵和为二维前缀和
		q.emplace_back(x1-1,y1-1,1,i);
		q.emplace_back(x1-1,y2,-1,i);
		q.emplace_back(x2,y1-1,-1,i);
		q.emplace_back(x2,y2,1,i);
	}

	{	//对 y 坐标的离散化
		vector<ll> tmp;
		for(ll i=1;i<=n;i++) tmp.emplace_back(v[i].second);
		for(auto &it:q) tmp.emplace_back(it.y);
		sort(tmp.begin(),tmp.end());
		tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
		for(ll i=1;i<=n;i++) v[i].second=lower_bound(tmp.begin(),tmp.end(),v[i].second)-tmp.begin()+1;
		for(auto &it:q) it.y=lower_bound(tmp.begin(),tmp.end(),it.y)-tmp.begin()+1;
	}
	
	//对 x 坐标的排序
	sort(q.begin(),q.end(),[](Ask &a,Ask &b){return a.x<b.x;});
	sort(v.begin()+1,v.end());
	
	H_Fenwick<ll> fwk(3e6+1);	//树状数组上界在 4*m+n 左右，取 3e6
	
	ll pos=1;
	for(auto &it:q){
		while(pos<=n&&v[pos].first<=it.x)	//添加 x 坐标小于当前询问 x 坐标的树点
			fwk.val_add(v[pos++].second,1);
		ans[it.p]+=fwk.query_Prefsum(it.y)*it.c;	//统计答案
	}
	
	for(ll i=1;i<=m;i++)
		cout<<ans[i]<<'\n';
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
