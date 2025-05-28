#include <bits/stdc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
//#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
//using namespace __gnu_pbds;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

//template <typename T, typename Compare = std::less<T>>
//using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

class H_PST{
public:
	class Info{
	public:
		ll ls,rs;
		
		ll sum,add;
		
		Info():ls(0),rs(0){}
		
		Info(ll pos,ll val):ls(0),rs(0){
			add=0;
			sum=val;
		}
	};
	
	void modify(ll &u,ll v,ll s,ll t,ll add){
		modify(u,v,1,n,s,t,add);
	}
	
	ll query(ll u,ll s,ll t){
		return query(u,1,n,s,t,0);
	}
	
	H_PST(ll _n){
		n=_n;
		tot=0;
		tr.assign(4*n+5,Info());
	}
	
	template<typename V>
	H_PST(ll _n,const V &vals,ll &rt){
		n=_n;
		tot=0;
		tr.assign(1e7,Info());
		build_tree(rt,1,n,vals);
	}
	
private:
	ll n,tot;
	vector<Info> tr;
	
	template<typename V>
	void build_tree(ll &u,ll l,ll r,const V &vals){
		u=++tot;
		
		if(l==r){
			tr[u]=Info(l,vals[l]);
			return;
		}
		
		ll mid=l+r>>1;
		build_tree(tr[u].ls,l,mid,vals);
		build_tree(tr[u].rs,mid+1,r,vals);
		
		tr[u].sum=tr[tr[u].ls].sum+tr[tr[u].rs].sum;
	}
	
	void modify(ll &u,ll v,ll l,ll r,ll s,ll t,ll add){
		u=++tot;
		tr[u]=tr[v];
		
		if(l>=s&&r<=t){
			tr[u].add+=add;
			return;
		}
		
		tr[u].sum+=(min(t,r)-max(l,s/*t*/)+1)*add;
		ll mid=l+r>>1;
		if(mid>=s)
			modify(tr[u].ls,tr[v].ls,l,mid,s,t,add);
		if(mid+1<=t)
			modify(tr[u].rs,tr[v].rs,mid+1,r,s,t,add);
	}
	
	ll query(ll u,ll l,ll r,ll s,ll t,ll add){
		if(!u)
			return 0;
		
		add+=tr[u].add;
		if(l>=s&&r<=t)
			return tr[u].sum+add*(r-l+1);
		
		ll mid=l+r>>1,res=0;
		if(mid>=s)
			res+=query(tr[u].ls,l,mid,s,t,add);
		if(mid+1<=t)
			res+=query(tr[u].rs,mid+1,r,s,t,add);
		return res;
	}
	
};

void solve(){
	ll n,m,now=0;
	cin>>n>>m;
	
	vector<ll> v(n+1,0);
	vector<ll> rt(m+1,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	H_PST pst(n,v,rt[0]);
	
	while(m--){
		string op;
		ll l,r,x;
		cin>>op;
		if(op[0]=='C'){
			cin>>l>>r>>x;
			pst.modify(rt[now+1],rt[now],l,r,x);
			now++;
		}
		else if(op[0]=='Q'){
			cin>>l>>r;
//			OOO
			cout<<pst.query(rt[now],l,r)<<endl;
		}
		else if(op[0]=='H'){
			cin>>l>>r>>x;
//			OOO
			cout<<pst.query(rt[x],l,r)<<endl;
		}
		else{
			cin>>x;
			for(;now>x;now--)
				rt[now]=0;
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
