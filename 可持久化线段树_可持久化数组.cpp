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

ll n,m,cnt,ver;
ll root[1000010];

struct Node{	//树节点
	ll lson,rson,val;
}tr[40000010];

void build_tree(ll &rt,ll l,ll r,ll pos,ll key){	//建树
	if(!rt) rt=++cnt;	//动态开点的固定操作，如果节点不存在则建立（同时由于传入的是引用，能够同时建立父子关系/根节点列表）
	
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

void update(ll &rt,ll pre,ll l,ll r,ll pos,ll key){	//修改操作：将pos位置 的值改为key
	
	//	pre 是前一版本的树上的对应节点，用于做参照，给新节点和前一版本的树上不受修改影响的那一半子树连边
	
	rt=++cnt;	//动态开点
	
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

ll query(ll rt,ll l,ll r,ll pos){	//查询某一点的数值
	if(l==r)
		return tr[rt].val;
	
	ll mid=l+((r-l)>>1);
	if(pos<=mid)
		return query(tr[rt].lson,l,mid,pos);
	else
		return query(tr[rt].rson,mid+1,r,pos);
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin>>n>>m;
	
	ll x;
	root[0]=++cnt;
	for(int i=1;i<=n;i++){
		cin>>x;
		build_tree(root[0],1,n,i,x);
	}
//	cout<<">>Tree Biult"<<endl;
	ll v,op,loc,key;
	for(int i=1;i<=m;i++){
		cin>>v>>op;
		if(op==1){
			cin>>loc>>key;
			root[++ver]=++cnt;
			update(root[ver],root[v],1,n,loc,key);
		}
		else{
			cin>>loc;
			root[++ver]=root[v];
			cout<<query(root[v],1,n,loc)<<endl;
		}
	}
	
	return 0;
}
