#include <bits/extc++.h>
#define OOO cout<<">>>>"<<endl;	//调试标识

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

const ll INF = 4e18, Mod1 = 1e9+7, Mod2=998244353, base=65537;

ll pm1[100001],pm2[100001],ipm1[100001],ipm2[100001];

ll tt=1;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a,ll Mod){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

void init(){
	pm1[0]=pm2[0]=1;
	ipm1[0]=ipm2[0]=1;
	ll ib1=inv(base,Mod1),ib2=inv(base,Mod2);
	for(ll i=1;i<=100000;i++){
		pm1[i]=pm1[i-1]*base%Mod1;
		pm2[i]=pm2[i-1]*base%Mod2;
		ipm1[i]=ipm1[i-1]*ib1%Mod1;
		ipm2[i]=ipm2[i-1]*ib2%Mod2;
	}
}

class Lhash{	//左侧的右括号哈希（左侧低位）
public:
	ll hs1,hs2,len;
	
	Lhash():hs1(0),hs2(0),len(0){}
	
	friend Lhash operator + (const Lhash &ls,const Lhash &rs){
		Lhash res;
		res.len=ls.len+rs.len;
		res.hs1=(ls.hs1+rs.hs1*pm1[ls.len])%Mod1;
		res.hs2=(ls.hs2+rs.hs2*pm2[ls.len])%Mod2;
		return res;
	}
	
	friend Lhash operator - (const Lhash &ls,const Lhash &rs){	//ls是整体 rs是前缀
		Lhash res;
		res.len=ls.len-rs.len;
		res.hs1=(ls.hs1-rs.hs1+Mod1)%Mod1*ipm1[rs.len]%Mod1;
		res.hs2=(ls.hs2-rs.hs2+Mod2)%Mod2*ipm2[rs.len]%Mod2;
		return res;
	}
	
	Lhash(ll val){
		hs1=val%Mod1;
		hs2=val%Mod2;
		len=1;
	}
	
};

class Rhash{	//右侧的左括号哈希（右侧低位）
public:
	ll hs1,hs2,len;
	
	Rhash():hs1(0),hs2(0),len(0){}
	
	friend Rhash operator + (const Rhash &ls,const Rhash &rs){
		Rhash res;
		res.len=ls.len+rs.len;
		res.hs1=(rs.hs1+ls.hs1*pm1[rs.len])%Mod1;
		res.hs2=(rs.hs2+ls.hs2*pm2[rs.len])%Mod2;
		return res;
	}
	
	friend Rhash operator - (const Rhash &ls,const Rhash &rs){	//ls是整体 rs是前缀
		Rhash res;
		res.len=ls.len-rs.len;
		res.hs1=(ls.hs1-rs.hs1+Mod1)%Mod1*ipm1[rs.len]%Mod1;
		res.hs2=(ls.hs2-rs.hs2+Mod2)%Mod2*ipm2[rs.len]%Mod2;
		return res;
	}
	
	Rhash(ll val){
		hs1=val%Mod1;
		hs2=val%Mod2;
		len=1;
	}
	
};

bool operator == (const Lhash &a,const Rhash &b){
	return (a.len==b.len&&a.hs1==b.hs1&&a.hs2==b.hs2);
}

Rhash operator - (const Rhash &ls,const Lhash &rs){	//ls是整体 rs是前缀
	Rhash res;
	res.len=ls.len-rs.len;
	res.hs1=(ls.hs1-rs.hs1+Mod1)%Mod1*ipm1[rs.len]%Mod1;
	res.hs2=(ls.hs2-rs.hs2+Mod2)%Mod2*ipm2[rs.len]%Mod2;
	return res;
}

Lhash operator - (const Lhash &ls,const Rhash &rs){	//ls是整体 rs是前缀
	Lhash res;
	res.len=ls.len-rs.len;
	res.hs1=(ls.hs1-rs.hs1+Mod1)%Mod1*ipm1[rs.len]%Mod1;
	res.hs2=(ls.hs2-rs.hs2+Mod2)%Mod2*ipm2[rs.len]%Mod2;
	return res;
}

class Node{
public:
	ll l,r,tg;
	Lhash lh;
	Rhash rh;
	Node():l(0),r(0),tg(0),lh(Lhash()),rh(Rhash()){}
	Node(ll pos,ll val):l(pos),r(pos),tg(1){
		if(val<0){
			lh=Lhash(-val);
			rh=Rhash();
		}else{
			rh=Rhash(val);
			lh=Lhash();
		}
	}
};

class SegmentTree{
public:
	ll n,top;
	vector<Node> tr;
	vector<ll> stk;
	vector<Rhash> seq;
	
	SegmentTree(ll _n){
		n=_n;
		tr.assign(4*n+5,Node());
		seq.assign(50,Rhash());
		stk.assign(50,0);
	}
	
	void build(vector<ll> &val){
		build(1,1,n,val);
	}
	
	Node merge(ll ls,ll rs){
		Node res;
		auto &ltr=tr[ls],&rtr=tr[rs];
		
		res.l=ltr.l;
		res.r=rtr.r;
		
		res.tg=ltr.tg&&rtr.tg;
		
		if(res.tg){
			if(ltr.rh.len==rtr.lh.len){
				res.lh=ltr.lh;
				res.rh=rtr.rh;
				Lhash pref=Lcalc(rs,ltr.rh.len);
				if(!(pref==ltr.rh)){
					res.tg=0;
				}
			}else if(ltr.rh.len<rtr.lh.len){
				
				res.rh=rtr.rh;
				
				Lhash pref=Lcalc(rs,ltr.rh.len);
				
				if(pref==ltr.rh){
					res.lh=ltr.lh+(rtr.lh-pref);
				}else{
					res.tg=0;
				}
				
			}else{
				
				res.lh=ltr.lh;
				
				Rhash pref=Rcalc(ls,rtr.lh.len);
				
				if(rtr.lh==pref){
					res.rh=(ltr.rh-pref)+rtr.rh;
				}else{
					res.tg=0;
				}
			}
		}
		
		return res;
	}
	
	Lhash Lcalc(ll u,ll len){
		if(len==0) return Lhash();
		if(len==tr[u].lh.len) return tr[u].lh;
		if(tr[u*2].lh.len>=len) return Lcalc(u*2,len);
		return tr[u*2].lh+(Lcalc(u*2+1,len-tr[u*2].lh.len+tr[u*2].rh.len)-tr[u*2].rh);
	}
	
	Rhash Rcalc(ll u,ll len){
//		cout<<"!! "<<u<<' '<<len<<endl;
		if(len==0) return Rhash();
		if(len==tr[u].rh.len) return tr[u].rh;
		if(tr[u*2+1].rh.len>=len) return Rcalc(u*2+1,len);
		return (Rcalc(u*2,len-tr[u*2+1].rh.len+tr[u*2+1].lh.len)-tr[u*2+1].lh)+tr[u*2+1].rh;
	}
	
	void modify(ll pos,ll key){
		modify(1,1,n,pos,key);
	}
	
	Rhash S_Rcalc(ll u,ll len){
		
		if(len==0) return Rhash();
		
		if(len==seq[u].len) return seq[u];
		
		if(len<=tr[stk[u]].rh.len) return Rcalc(stk[u],len);
		
		return (S_Rcalc(u-1,len-tr[stk[u]].rh.len+tr[stk[u]].lh.len)-tr[stk[u]].lh)+tr[stk[u]].rh;
	}
	
	bool query(ll l,ll r){
		top=0;
		getseg(1,1,n,l,r);
		
//		cout<<"Top "<<top<<' '<<stk[top]<<endl;
		
		for(ll i=1;i<=top;i++){
			auto &cur=tr[stk[i]];
			if(!cur.tg) return 0;
			if(seq[i-1].len<cur.lh.len) return 0;
//			cout<<"!! "<<S_Rcalc(i-1,cur.lh.len).len<<endl;
			if(cur.lh==S_Rcalc(i-1,cur.lh.len)){
				seq[i]=(seq[i-1]-cur.lh)+cur.rh;
			}else return 0;
		}
//		cout<<"Len "<<seq[top].len<<endl;
		
		return seq[top].len==0;
	}
	
private:
	void build(ll u,ll l,ll r,vector<ll> &val){
		if(l==r){
			tr[u]=Node(l,val[l]);
			
//			cout<<">>> "<<u<<' '<<tr[u].lh.hs1<<' '<<tr[u].rh.hs1<<' '<<tr[u].tg<<endl;
			
			return;
		}
		
		ll mid=l+r>>1;
		build(u*2,l,mid,val);
		build(u*2+1,mid+1,r,val);
		tr[u]=merge(u*2,u*2+1);
//		cout<<">>> "<<u<<' '<<tr[u].lh.hs1<<' '<<tr[u].rh.hs1<<' '<<tr[u].tg<<endl;
	}
	
	void modify(ll u,ll l,ll r,ll pos,ll key){
		if(l==r){
			tr[u]=Node(l,key);
			return;
		}
		
		ll mid=l+r>>1;
		
		if(pos<=mid){
			modify(u*2,l,mid,pos,key);
		}else{
			modify(u*2+1,mid+1,r,pos,key);
		}
		tr[u]=merge(u*2,u*2+1);	
	}
	
	void getseg(ll u,ll l,ll r,ll s,ll t){
		if(l>=s&&r<=t){
			stk[++top]=u;
			return;
		}
		
		ll mid=l+r>>1;
		if(s<=mid) getseg(u*2,l,mid,s,t);
		if(t>=mid+1) getseg(u*2+1,mid+1,r,s,t);
	}
	
};

void solve(){
	ll n,k,m;
	cin>>n>>k;
	
	vector<ll> v(n+1,0);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
	}
	
	SegmentTree sgm(n);
	sgm.build(v);
	
	cin>>m;
	
	while(m--){
		ll op,l,r;
		cin>>op>>l>>r;
		if(op==1){
			sgm.modify(l,r);
		}else{
			if(sgm.query(l,r)){
				cout<<"Yes"<<endl;
			}else{
				cout<<"No"<<endl;
			}
		}
	}
	
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	init();
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
