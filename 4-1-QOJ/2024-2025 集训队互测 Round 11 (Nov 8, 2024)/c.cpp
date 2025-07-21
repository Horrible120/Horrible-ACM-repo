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

std::ostream &operator<<(std::ostream &os, i128 j) {
	std::string ans;
	auto write = [&](auto &&self, i128 x) -> void {
		if (x < 0) {
			ans += '-';
			x = -x;
		}
		if (x > 9) {
			self(self, x / 10);
		}
		ans += x % 10 + '0';
	};
	write(write, j);
	return os << ans;
}


class H_sgm{
public:
	class Info{	//节点信息类
	public:
		ll l,r;	//左右边界
		i128 max_val;	// A 数组的区间最大值
		i128 max_sum;	// A 数组的区间前缀最大值和
		i128 b_sum;		// B 数组的区间和
		Info():l(0),r(0),max_val(0),max_sum(0),b_sum(0){}
	};
	
	class Tag{	//节点标记类
	public:
		i128 add_val;	//对 B 数组的区间加标记
		i128 max_add_cnt;	//对 B 数组的加区间前缀最大值标记
		Tag():add_val(0),max_add_cnt(0){}
	};
	
	ll n;	//元素个数
	vector<Info> info;
	vector<Tag> tag;
	
	H_sgm(ll _n){
		n=_n;
		info.resize(4*n+5);
		tag.resize(4*n+5);
	}
	
	i128 query_b_max(ll u,i128 pre_max){
		Info &cur=info[u];
		
		if(cur.l==cur.r)
			return max(cur.max_sum,pre_max);
		
		Info &lhs=info[u*2],&rhs=info[u*2+1];
		if(lhs.max_val<=pre_max){
			return pre_max*(lhs.r-lhs.l+1)+query_b_max(u*2+1,pre_max);
		}
		else{
			return query_b_max(u*2,pre_max)+cur.max_sum-lhs.max_sum;
		}
	}
	
	i128 proc(ll u,i128 pre_max,ll c){
		Info &cur=info[u];
		if(cur.l==cur.r){
			i128 d=max(pre_max,cur.max_sum)*c;
			cur.b_sum+=d;
			return d;
		}

		Info &lhs=info[u*2],&rhs=info[u*2+1];
		if(lhs.max_val<=pre_max){
			i128 dl=c*(lhs.r-lhs.l+1)*pre_max;
			lhs.b_sum+=dl;
			tag[u*2].add_val+=c*pre_max;
			
			i128 dr=proc(u*2+1,max(pre_max,lhs.max_val),c);
			i128 d=dl+dr;
			cur.b_sum+=d;
			return d;
		}
		else{
			i128 dl=proc(u*2,pre_max,c);
			i128 dr=(cur.max_sum-lhs.max_sum)*c;
			i128 d=dl+dr;
			tag[u].max_add_cnt+=c;
			cur.b_sum+=d;
			return d;
		}
	}
	
	void build_tree(ll u,ll l,ll r,vector<ll> &vals){
		Info &cur=info[u];
		
		if(l==r){
			cur.l=cur.r=l;
			cur.max_val=vals[l];
			cur.b_sum=0;
			cur.max_sum=vals[l];
			
//			cout<<u<<' '<<l<<' '<<r<<" | "<<cur.max_sum<<' '<<cur.max_val<<endl;
			
			return;
		}
		
		Info &lhs=info[u*2],&rhs=info[u*2+1];
		ll mid=l+r>>1;
		build_tree(u*2,l,mid,vals);
		build_tree(u*2+1,mid+1,r,vals);
		
		cur.l=l;
		cur.r=r;
		cur.max_val=max(lhs.max_val,rhs.max_val);
		cur.max_sum=lhs.max_sum+query_b_max(u*2+1,lhs.max_val);
		cur.b_sum=lhs.b_sum+rhs.b_sum;
//		cout<<u<<' '<<l<<' '<<r<<" | "<<cur.max_sum<<' '<<cur.max_val<<endl;
	}
	
	void pushdown(ll u){
		Info &cur=info[u];
		Info &lhs=info[u*2],&rhs=info[u*2+1];
		Tag &ct=tag[u];
		
		if(ct.add_val){
			lhs.b_sum+=(lhs.r-lhs.l+1)*ct.add_val;
			rhs.b_sum+=(rhs.r-rhs.l+1)*ct.add_val;
			if(lhs.r>lhs.l){
				tag[u*2].add_val+=ct.add_val;
			}
			if(rhs.r>rhs.l){
				tag[u*2+1].add_val+=ct.add_val;
			}
		}
		
		if(ct.max_add_cnt){
			proc(u*2+1,lhs.max_val,ct.max_add_cnt);
		}
		
		ct=Tag();
	}
	
	void modify_1(ll u,ll pos,ll key){
		Info &cur=info[u];
		
		if(cur.l==cur.r){
			cur.max_val=cur.max_sum=key;
			return;
		}
		
		pushdown(u);
		
		ll mid=cur.l+cur.r>>1;
		if(pos<=mid){
			modify_1(u*2,pos,key);
		}
		else{
			modify_1(u*2+1,pos,key);
		}
		
		Info &lhs=info[u*2],&rhs=info[u*2+1];
		cur.max_val=max(lhs.max_val,rhs.max_val);
		cur.max_sum=lhs.max_sum+query_b_max(u*2+1,lhs.max_val);
		cur.b_sum=lhs.b_sum+rhs.b_sum;
	}
	
	void modify_2(ll u,ll s,ll t,i128 &pre_max){
		Info &cur=info[u];
		if(cur.l>=s&&cur.r<=t){
			
			proc(u,pre_max,1);
			
			pre_max=max(pre_max,cur.max_val);
			return;
		}
		
		pushdown(u);
		
		ll mid=(cur.l+cur.r)>>1;
		if(mid>=s){
			modify_2(u*2,s,t,pre_max);
		}
		if(mid+1<=t){
			modify_2(u*2+1,s,t,pre_max);
		}
		
		cur.b_sum=info[u*2].b_sum+info[u*2+1].b_sum;
	}
	
	void modify_2(ll s,ll t){
		i128 pre_max=-INF;
		modify_2(1,s,t,pre_max);
	}
	
	i128 query_b_sum(ll u,ll s,ll t){
		Info &cur=info[u];
		if(cur.l>=s&&cur.r<=t){
			return cur.b_sum;
		}
		
		pushdown(u);
		
		ll mid=cur.l+cur.r>>1;
		i128 res=0;
		if(mid>=s){
			res+=query_b_sum(u*2,s,t);
		}
		if(mid+1<=t){
			res+=query_b_sum(u*2+1,s,t);
		}
		return res;
	}
	
};



void solve(){
	ll n,m;
	cin>>n>>m;
	
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	H_sgm sgm(n);
	
	sgm.build_tree(1,1,n,v);
	for(ll i=1;i<=m;i++){
		ll op,x,y;
		cin>>op;
		if(op==1){
			cin>>x>>y;
			sgm.modify_1(1,x,y);
		}
		else if(op==2){
			cin>>x>>y;
			sgm.modify_2(x,y);
		}
		else{
			cin>>x>>y;
			cout<<sgm.query_b_sum(1,x,y)<<endl;
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
	}
	
	cout.flush();
	return 0;
}
