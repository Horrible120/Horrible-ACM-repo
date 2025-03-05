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

template<typename T>
class H_Fenwick{
public:
	ll n;
	vector<T> val;
	
	H_Fenwick(ll _n):n(_n){
		val.assign(n+1,0);
	}
	
	ll lb(ll x) {return x&-x;}
	
	T query_Prefsum(ll x){
		T res=0;
		while(x){
			res+=val[x];
			x-=lb(x);
		}
		return res;
	}
	
	T query_Rangesum(ll l,ll r){
		return query_Prefsum(r)-query_Prefsum(l-1);
	}
	
	void val_add(ll pos,T key){
		while(pos<=n){
			val[pos]+=key;
			pos+=lb(pos);
		}
	}
	
	void val_modify(ll pos,T key){
		val_add(pos,key-query_Rangesum(pos,pos));
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<pair<ll,ll>> v(n+1);
	vector<tuple<ll,ll,ll,ll>> q;
	vector<ll> ans(m+1);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i].first>>v[i].second;
		v[i].first++;
		v[i].second++;
	}
	
	for(ll i=1;i<=m;i++){
		ll x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		x1++,y1++,x2++,y2++;
		q.emplace_back(x1-1,y1-1,1,i);
		q.emplace_back(x1-1,y2,-1,i);
		q.emplace_back(x2,y1-1,-1,i);
		q.emplace_back(x2,y2,1,i);
	}
	
	{
		auto cmp=[](tuple<ll,ll,ll,ll> &a,tuple<ll,ll,ll,ll> &b){
			auto &[x1,y1,a1,b1]=a;
			auto &[x2,y2,a2,b2]=b;
			return y1<y2;
		};
		auto tmp=q;
		sort(tmp.begin()+1,tmp.end(),cmp);
		tmp.erase(unique(tmp.begin()+1,tmp.end()),tmp.end());
		for(ll i=1;i<=2*m;i++){
			
		}
			y[i]=lower_bound(tmp.begin()+1,tmp.end(),y[i])-tmp.begin();
		for()
	}
	
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
