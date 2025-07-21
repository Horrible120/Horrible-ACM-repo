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
	ll n,m;
	cin>>n>>m;
	
	class Node{
	public:
		ll cnt;
		long double max_hi;
		Node()=default;
		Node(ll pos,long double hi):max_hi(hi){
			cnt=(hi>0);
		}
	};
	
	vector<Node> tr(4*n+1,Node());
	
	auto update=[&](auto &&self,ll u,ll l,ll r,long double hi)->ll{
		ll mid=l+r>>1;
		if(l==r)
			return tr[u].max_hi>hi;
		else if(tr[u].max_hi<=hi)
			return 0;
		else if(tr[u*2].max_hi<=hi)
			return self(self,u*2+1,mid+1,r,hi);
		else
			return self(self,u*2,l,mid,hi)+tr[u].cnt-tr[u*2].cnt;
	};
	
	auto build_tree=[&](auto &&self,ll u,ll l,ll r)->void{
		if(l==r){
			tr[u]=Node(l,0);
			return;
		}
		ll mid=l+r>>1;
		
		self(self,u*2,l,mid);
		self(self,u*2+1,mid+1,r);
		
		tr[u].max_hi=max(tr[u*2].max_hi,tr[u*2+1].max_hi);
		tr[u].cnt=tr[u*2].cnt+update(update,u*2+1,mid+1,r,tr[u*2].max_hi);
	};
	
	auto modify=[&](auto &&self,ll u,ll l,ll r,ll pos,long double hi)->void{
		if(l==r){
			tr[u]=Node(pos,hi);
			return;
		}
		
		ll mid=l+r>>1;
		
		if(pos<=mid)
			self(self,u*2,l,mid,pos,hi);
		else
			self(self,u*2+1,mid+1,r,pos,hi);
		
		tr[u].max_hi=max(tr[u*2].max_hi,tr[u*2+1].max_hi);
		tr[u].cnt=tr[u*2].cnt+update(update,u*2+1,mid+1,r,tr[u*2].max_hi);
//		cout<<'['<<l<<','<<r<<']'<<' '<<tr[u].cnt<<endl;
	};
	
	build_tree(build_tree,1,1,n);
	
	for(ll i=1;i<=m;i++){
		ll pos,x;
		cin>>pos>>x;
//		cout<<(long double)x/pos<<endl;
		modify(modify,1,1,n,pos,(long double)x/pos);
//		OOO
		cout<<tr[1].cnt<<endl;
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
