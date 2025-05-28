#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;
class H_sgm{
public:
	
	ll top,low,tot,rt;
	class Info{
	public:
		ll cnt,sum,lhs,rhs;
		Info():lhs(0),rhs(0),cnt(0),sum(0){}
		Info(ll val){
			cnt=1;
			sum=val;
			lhs=rhs=0;
		}
	};
	
	ll n=0;
	vector<Info> tr;
	
	H_sgm(ll _n){
		tr.assign(_n*32+1,Info());
		rt=0;
		tot=0;
		top=1e9;
		low=1;
	}
	
	void insert(ll val,ll k){
		insert(rt,low,top,val,k);
	}
	
	ll find_fir(ll sum){
		return find_fir(rt,low,top,sum);
	}
	
private:
	void insert(ll &u,ll l,ll r,ll val,ll k){
		if(!u)
			u=++tot;
//		cout<<"!!!! "<<u<<' '<<l<<' '<<r<<' '<<val<<endl;
		if(l==r){
			tr[u].cnt+=k;
			tr[u].sum+=k*val;
			return;
		}
		ll mid=l+r>>1;
		if(val<=mid)
			insert(tr[u].lhs,l,mid,val,k);
		else
			insert(tr[u].rhs,mid+1,r,val,k);
		tr[u].cnt+=k;
		tr[u].sum+=k*val;
	}
	
	ll find_fir(ll u,ll l,ll r,ll sum){
		if(u==0)
			return 0ll;
		if(sum>=tr[u].sum)
			return tr[u].cnt;
		if(l==r)
			return sum/l;
		ll mid=l+r>>1;
		
		if(sum>=tr[tr[u].lhs].sum)
			return find_fir(tr[u].rhs,mid+1,r,sum-tr[tr[u].lhs].sum)+tr[tr[u].lhs].cnt;
		else
			return find_fir(tr[u].lhs,l,mid,sum);
	}
	
};

void solve(){
	ll n,q,psum=0;
	cin>>n>>q;
	
	vector<ll> v(n+1,0);
	
	H_sgm sgm(n+q);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		if(v[i]>0)
			sgm.insert(v[i],1);
		else
			psum+=-v[i];
	}
	
	while(q--){
		ll x,y;
		
		cin>>x>>y;
		if(v[x]>0)
			sgm.insert(v[x],-1);
		else
			psum-=-v[x];
		
		v[x]=y;
		
		
		if(v[x]>0)
			sgm.insert(v[x],1);
		else
			psum+=-v[x];
		
//		OOo
		cout<<sgm.find_fir(psum)+1<<endl;		
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
