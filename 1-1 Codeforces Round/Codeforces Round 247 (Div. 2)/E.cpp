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

class H_sgm{
public:
	ll n,tot;
	class Node{
	public:
		ll ls,rs,sum,cnt;
		Node()=default;
		Node(ll val):sum(val),ls(0),rs(0),cnt(1){}
	};
	
	vector<Node> tr;
	
	H_sgm(ll _n){
		n=_n;
		tot=0;
		tr.assign(5000000,Node());
	}
	
	void add_val(ll &u,ll l,ll r,ll val,ll k){
		if(!u)
			u=++tot;
//		cout<<u<<' '<<l<<' '<<r<<' '<<val<<' '<<k<<endl;
		auto &cur=tr[u];
		
		if(l==r){
			cur.sum+=k*val;
			cur.cnt+=k;
			return;
		}
		
		ll mid=(l+r)/2;
		
		if(val<=mid)
			add_val(cur.ls,l,mid,val,k);
		else
			add_val(cur.rs,mid+1,r,val,k);
		
		cur.sum=tr[cur.ls].sum+tr[cur.rs].sum;
		cur.cnt=tr[cur.ls].cnt+tr[cur.rs].cnt;
	}
	
	pll query(ll u,ll l,ll r,ll s,ll t){
		if(!u)
			return make_pair(0,0);
		
//		cout<<u<<' '<<l<<' '<<r<<' '<<s<<' '<<t<<endl;
		
		auto &cur=tr[u];
		
		if(l>=s&&r<=t)
			return make_pair(cur.sum,cur.cnt);
		
		ll mid=(l+r)/2;
		
		pll res=make_pair(0,0);
		
		if(mid>=s){
			auto [sum,cnt]=query(cur.ls,l,mid,s,t);
			res.first+=sum;
			res.second+=cnt;
		}
			
		if(mid+1<=t){
			auto [sum,cnt]=query(cur.rs,mid+1,r,s,t);
			res.first+=sum;
			res.second+=cnt;
		}
		return res;
	}
};

void solve(){
	ll n,q,rt=0;
	cin>>n>>q;
	vector<ll> v(n+1,0);
	
	H_sgm sgm(n);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		sgm.add_val(rt,0,1e9,v[i],1);
	}
		
	while(q--){
		ll op,p,x;
		cin>>op;
		if(op==1){
			cin>>p>>x;
			sgm.add_val(rt,0,1e9,v[p],-1);
			v[p]=x;
			sgm.add_val(rt,0,1e9,v[p],1);
		}
		else{
			cin>>x;
			ll l=0,r=1e9;
			while(l<r){
				ll mid=(l+r+1)/2;
				auto [sum,cnt]=sgm.query(rt,0,1e9,0,mid);
				if(cnt==0)
					l=mid+1;
				else if(sum+x<mid*cnt)
					r=mid-1;
				else
					l=mid;
			}
			auto [sum,cnt]=sgm.query(rt,0,1e9,0,l);

			cout<<(long double)(sum+x)/cnt<<endl;
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
