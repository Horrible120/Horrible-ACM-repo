//	可持久化并查集 初学练习题 模板
//	https://www.luogu.com.cn/problem/P3402

#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>

using namespace std;

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
Mod = 1e9+7;

ll n,m;
ll root[200010];

struct Node{
	ll lson,rson,val;
};

struct Array{
	Node tr[7000010];
	ll root[1000010],cnt;
	
//	初始化fa数组
	void build_dsu_fa(ll &rt,ll l,ll r){
		if(!rt) rt=++cnt;
		
		if(l==r){
			tr[rt].val=l;
			return;
		}
		
		ll mid=l+((r-l)>>1);
		build_dsu_fa(tr[rt].lson,l,mid);
		build_dsu_fa(tr[rt].rson,mid+1,r);
	}
	
//	初始化dep数组
	void build_dsu_dep(ll &rt,ll l,ll r){
		if(!rt) rt=++cnt;
		
		if(l==r){
			tr[rt].val=1;
			return;
		}
		
		ll mid=l+((r-l)>>1);
		build_dsu_dep(tr[rt].lson,l,mid);
		build_dsu_dep(tr[rt].rson,mid+1,r);
	}
//	本题中无用
	void build_tree(ll &rt,ll l,ll r,ll pos,ll key){
		if(!rt) rt=++cnt;
		
		if(l==r){
			tr[rt].val=key;
			return;
		}
		
		ll mid=l+((r-l)>>1);
		if(pos<=mid)
			build_tree(tr[rt].lson,l,mid,pos,key);
		else
			build_tree(tr[rt].rson,mid+1,r,pos,key);
	}
	
	void update(ll &rt,ll pre,ll l,ll r,ll pos,ll key){	//修改操作：将pos位置的值改为key
		rt=++cnt;
		
		if(l==r){
			tr[rt].val=key;
			return;
		}
		
		ll mid=l+((r-l)>>1);
		if(pos<=mid){
			tr[rt].rson=tr[pre].rson;
			update(tr[rt].lson,tr[pre].lson,l,mid,pos,key);
		}
		else{
			tr[rt].lson=tr[pre].lson;
			update(tr[rt].rson,tr[pre].rson,mid+1,r,pos,key);
		}
	}
	
//	查询某一位置的值
	ll query(ll rt,ll l,ll r,ll pos){
		if(l==r)
			return tr[rt].val;
		
		ll mid=l+((r-l)>>1);
		if(pos<=mid)
			return query(tr[rt].lson,l,mid,pos);
		else
			return query(tr[rt].rson,mid+1,r,pos);
	}
	
//	获取集合的根节点
	ll get_fa(ll ver,ll pos){
		ll fa=query(root[ver],1,n,pos);
		if(fa==pos)
			return fa;
		return get_fa(ver,fa);
	}
	
//	判断是否在同一集合
	ll dsu_judge(ll ver,ll x,ll y){
		ll a=get_fa(ver,x),b=get_fa(ver,y);
		return a==b;
	}
	
	Array(){}
	
};

Array fa,dep;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin>>n>>m;
	
	fa.build_dsu_fa(fa.root[0],1,n);
	dep.build_dsu_dep(dep.root[0],1,n);
	
	ll op,a,b;
	for(int i=1;i<=m;i++){
		cin>>op;
		if(op==1){
			cin>>a>>b;
			a=fa.get_fa(i-1,a);
			b=fa.get_fa(i-1,b);
			if(a!=b){
				ll x=dep.query(dep.root[i-1],1,n,a),
				   y=dep.query(dep.root[i-1],1,n,b);
				if(x<y)
					swap(x,y),swap(a,b);
				fa.update(fa.root[i],fa.root[i-1],1,n,b,a);
				if(x==y)
					dep.update(dep.root[i],dep.root[i-1],1,n,a,x+1);	//我cnmlg********
				else
					dep.root[i]=dep.root[i-1];
			}
			else{
				fa.root[i]=fa.root[i-1];
				dep.root[i]=dep.root[i-1];
			}
		}
		else if(op==2){
			cin>>a;
			fa.root[i]=fa.root[a];
			dep.root[i]=dep.root[a];
		}
		else if(op==3){
			cin>>a>>b;
			fa.root[i]=fa.root[i-1];
			dep.root[i]=dep.root[i-1];
			cout<<fa.dsu_judge(i,a,b)<<'\n';
		}
	}
	
	cout.flush();
	
	return 0;
}
