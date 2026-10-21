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

template<typename T>
class H_Fenwick{	//树状数组 类
public:
	ll n;	//总的元素个数
	vector<T> val;	//储存树状数组的数据
	
	H_Fenwick(ll _n):n(_n){	// n 个元素的初始化
		val.assign(n+1,0);
	}
	
	ll lb(ll x) {return x&-x;}	//求 lowbit
	
	T query_Prefsum(ll pos){	//求前缀和
		T res=0;
		while(pos){
			res+=val[pos];
			pos-=lb(pos);
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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0),odd,even;
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		if(i&1)
			odd.emplace_back(v[i]);
		else
			even.emplace_back(v[i]);
	}
	
	H_Fenwick<ll> fwk(n);
	
	if(n&1){
		
		ll rv=0;
		for(ll i=odd.size()-1;i>=0;i--){
			rv+=fwk.query_Prefsum(odd[i]);
			fwk.val_add(odd[i],1);
		}
		
		{
			H_Fenwick<ll> fwk2(n);
			for(ll i=even.size()-1;i>=0;i--){
				rv+=fwk2.query_Prefsum(even[i]);
				fwk2.val_add(even[i],1);
			}
		}
		
		sort(even.begin(),even.end());
		sort(odd.begin(),odd.end());
		ll m=odd.size();
		if(rv&1)
			swap(odd[m-1],odd[m-2]);
		for(ll i=1;i<=n;i++){
			if(i&1)
				cout<<odd[i/2]<<' ';
			else
				cout<<even[i/2-1]<<' ';
		}
		cout<<endl;
	}
	else{
		
		ll rv=0;
		for(ll i=even.size()-1;i>=0;i--){
			rv+=fwk.query_Prefsum(even[i]);
			fwk.val_add(even[i],1);
		}
		
		{
			H_Fenwick<ll> fwk2(n);
			for(ll i=odd.size()-1;i>=0;i--){
				rv+=fwk2.query_Prefsum(odd[i]);
				fwk2.val_add(odd[i],1);
			}
		}
		
		sort(odd.begin(),odd.end());
		sort(even.begin(),even.end());
		
		ll m=even.size();
		if(rv&1)
			swap(even[m-1],even[m-2]);
		for(ll i=1;i<=n;i++){
			if(i&1)
				cout<<odd[i/2]<<' ';
			else
				cout<<even[i/2-1]<<' ';
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
