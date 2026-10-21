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
	ll n,q;
	cin>>n>>q;
	vector<ll> v(n+1),pos(n+1);
	vector<pll> p(n+1);
	vector<tuple<ll,ll,ll,ll>> qst(q+1);
 	for(ll i=1;i<=n;i++){
		cin>>v[i];
		pos[v[i]]=i;
		p[i]=make_pair(v[i],i);
	}
	
	for(ll i=1;i<=q;i++){
		auto &[k,l,r,d]=qst[i];
		cin>>l>>r>>k;
		d=i;
	}
	
	sort(qst.begin()+1,qst.end());
	sort(p.begin()+1,p.end());
	
	H_Fenwick<ll> fwk(n);
	
	ll tp=1;
	vector<ll> ans(q+1,0);
	for(ll i=1;i<=q;i++){
		auto &[k,ql,qr,d]=qst[i];
		
		while(tp<=n&&p[tp].first<k)
			fwk.val_add(p[tp++].second,1);
		
		if(pos[k]<ql||pos[k]>qr){
			ans[d]=-1;
			continue;
		}
		
		ll l=ql,r=qr,pl=0,ph=0,needl=0,needh=0,inl=0,inh=0;
		while(l<r){
			ll mid=(l+r)/2;
			if(pos[k]==mid) break;
			if(pos[k]>mid){
				if(v[mid]>k)
					needl++,inh++;
				else
					pl++;
				l=mid+1;
			}
			if(pos[k]<mid){
				if(v[mid]<k)
					needh++,inl++;
				else
					ph++;
				r=mid-1;
			}
		}
		
		if(k-1<needl+pl||n-k<needh+ph){
			ans[d]=-1;
			continue;
		}
		{
			ans[d]=needl+needh+max(0ll,needl-inl)+max(0ll,needh-inh);
		}
	}
//	OOO
	for(ll i=1;i<=q;i++)
		cout<<ans[i]<<' ';
	cout<<endl;
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
