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

class Info{
public:
	ll lhs,rhs;
	ll dbt,coin,sum;	//区间被哥布林收走的钱 剩余的钱 还欠哥布林的钱
	ll aa,bb;	//保存原始的 a 和 b
	Info():lhs(0),rhs(0),dbt(0),coin(0),sum(0){}
	Info(ll _a,ll _b):lhs(0),rhs(0){	//初始构造函数
		aa=_a;
		bb=_b;
		dbt=max(0ll,_b-_a);
		coin=max(0ll,_a-_b);
		sum=min(_a,_b);
	}
	friend Info operator + (const Info &_l,const Info &_r){
		Info res=Info();
		ll tmp=min(_l.coin,_r.dbt);	//左边剩余的钱最多能补上右边多少欠款
		res.sum=_l.sum+_r.sum+tmp;
		res.coin=_l.coin+_r.coin-tmp;
		res.dbt=_l.dbt+_r.dbt-tmp;
		return res;
	}
};

void solve(){
	ll n,m;
	cin>>n>>m;
	vector<ll> a(n+1,0),b(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>a[i];		
	}
	for(ll i=1;i<=n;i++){
		cin>>b[i];
	}
	
	ll tot=0;
	vector<Info> tr(n*20+1);
	vector<ll> roots(m+1,0);
	
	auto pushup=[&](ll u){	//更新节点
		ll ul=tr[u].lhs,ur=tr[u].rhs;
		ll tmp=min(tr[ul].coin,tr[ur].dbt);
		tr[u].sum=tr[ul].sum+tr[ur].sum+tmp;
		tr[u].coin=tr[ul].coin+tr[ur].coin-tmp;
		tr[u].dbt=tr[ul].dbt+tr[ur].dbt-tmp;
	};
	
	auto build_tree=[&](auto &&self,ll &u,ll l,ll r)->void{	//建树
		u=++tot;
		if(l==r){
			tr[u]=Info(a[l],b[l]);	//叶子节点
			return;
		}
		ll mid=l+r>>1;
		self(self,tr[u].lhs,l,mid);
		self(self,tr[u].rhs,mid+1,r);
		pushup(u);
	};
	
	auto modify_1=[&](auto &&self,ll &u,ll pre,ll l,ll r,ll pos,ll key)->void{	//修改 pos 处的 a 值为 key
		u=++tot;
		tr[u]=tr[pre];
		if(l==r){
			tr[u]=Info(key,tr[u].bb);
			return;
		}
		ll mid=l+r>>1;
		if(pos<=mid){
			self(self,tr[u].lhs,tr[pre].lhs,l,mid,pos,key);
		}else{
			self(self,tr[u].rhs,tr[pre].rhs,mid+1,r,pos,key);
		}
		pushup(u);
	};
	
	auto modify_2=[&](auto &&self,ll &u,ll pre,ll l,ll r,ll pos,ll key)->void{	//修改 pos 处的 b 值为 key
		u=++tot;
		tr[u]=tr[pre];
		if(l==r){
			tr[u]=Info(tr[u].aa,key);
			return;
		}
		ll mid=l+r>>1;
		if(pos<=mid){
			self(self,tr[u].lhs,tr[pre].lhs,l,mid,pos,key);
		}else{
			self(self,tr[u].rhs,tr[pre].rhs,mid+1,r,pos,key);
		}
		pushup(u);
	};
	
	auto query=[&](auto &&self,ll u,ll l,ll r,ll s,ll t,Info &res)->void{	//带状态查询 从左到右合并状态
		if(!u) return;
		if(l>=s&&r<=t){
			res=res+tr[u];	//合并状态
			return;
		}
		ll mid=l+r>>1;
		if(mid>=s){
			self(self,tr[u].lhs,l,mid,s,t,res);
		}
		if(mid+1<=t){
			self(self,tr[u].rhs,mid+1,r,s,t,res);
		}
	};
	
	auto query_a=[&](auto &&self,ll u,ll l,ll r,ll pos)->ll{	//查询某一处的 a 值
		if(!u) return 0;
		if(l==r){
			return tr[u].aa;
		}
		ll mid=l+r>>1,res=0;
		if(pos<=mid){
			return self(self,tr[u].lhs,l,mid,pos);
		}else{
			return self(self,tr[u].rhs,mid+1,r,pos);
		}
	};
	
	build_tree(build_tree,roots[0],1,n);
	
//	ll currt=0;
	
	for(ll i=1;i<=m;i++){
		ll op,x,y;
		cin>>op;
//		roots[i]=roots[i-1];
		if(op==1){
			cin>>x>>y;
			modify_1(modify_1,roots[i],roots[i-1],1,n,x,y);
		}else if(op==2){
			cin>>x>>y;
			modify_2(modify_2,roots[i],roots[i-1],1,n,x,y);
		}else if(op==3){
			cin>>x;
			roots[i]=roots[x];
		}else{
			ll k,cur=1;
			cin>>k;
			Info ans=Info();
			roots[i]=roots[i-1];
//			for(ll j=1;j<=n;j++){
//				cout<<"!!! "<<j<<' '<<query_a(query_a)
//			}
			
			for(ll j=1;j<=k;j++){	//暴力查询+合并
				cin>>x;
				if(x>cur){
					query(query,roots[i],1,n,cur,x-1,ans);
				}
				
//				cout<<cur<<' '<<x<<" | "<<ans.sum<<' '<<ans.coin<<' '<<ans.dbt<<endl;
				
				ans.coin+=query_a(query_a,roots[i],1,n,x);
				ans.sum+=(ans.coin+1)/2;
				ans.coin/=2;
				ans.dbt=0;
				cur=x+1;
				
//				cout<<cur<<' '<<x<<" | "<<ans.sum<<' '<<ans.coin<<' '<<ans.dbt<<endl;
			}
			if(cur<=n){
				query(query,roots[i],1,n,cur,n,ans);
			}
//			OOO
			cout<<ans.sum<<endl;
		}
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
