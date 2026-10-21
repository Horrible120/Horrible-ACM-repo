#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
const ll B=50;
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
	ll n,q;
	cin>>n>>q;
	vector<ll> a(n+1),val;
	vector<tuple<ll,ll,ll,ll>> qst(q+1);
	val.reserve(n+q);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		val.emplace_back(a[i]);
	}
	for(ll i=1;i<=q;i++){
		auto &[op,x,y,k]=qst[i];
		cin>>op>>x>>y;
		if(op==2)
			cin>>k;
		else
			val.emplace_back(y);
	}

	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	auto id=[&](ll x){
		return lower_bound(val.begin(),val.end(),x)-val.begin();
	};
	for(ll i=1;i<=n;i++)
		a[i]=id(a[i]);
	for(ll i=1;i<=q;i++){
		auto &[op,x,y,k]=qst[i];
		if(op==1)
			y=id(y);
	}

	vector<ull> tag(val.size());
	for(ll i=0;i<(ll)val.size();i++)
		tag[i]=rnd();
	vector<H_Fenwick<ll>> fwk;
	for(ll j=0;j<B;j++){
		fwk.emplace_back(n);
		for(ll i=1;i<=n;i++)
			fwk[j].val_add(i,(tag[a[i]]>>j)&1);
	}

	for(ll i=1;i<=q;i++){
		auto [op,x,y,k]=qst[i];
		if(op==1){
			for(ll j=0;j<B;j++){
				ll pre=(tag[a[x]]>>j)&1;
				ll nxt=(tag[y]>>j)&1;
				fwk[j].val_add(x,nxt-pre);
			}
			a[x]=y;
		}else{
			if(k==1){
				cout<<"YES\n";
				continue;
			}
			if((y-x+1)%k){
				cout<<"NO\n";
				continue;
			}

			bool ok=true;
			for(ll j=0;j<B;j++){
				if(fwk[j].query_Rangesum(x,y)%k){
					ok=false;
					break;
				}
			}
			cout<<(ok?"YES":"NO")<<'\n';
		}
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

//	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
