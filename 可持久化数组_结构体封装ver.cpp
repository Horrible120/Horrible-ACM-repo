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

ll n,m,ver;

struct Node{
	ll lson,rson,val;
};

struct Array{
	Node tr[37000010];
	ll root[1000010],cnt;
	
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
	
	ll query(ll rt,ll l,ll r,ll pos){
		if(l==r)
			return tr[rt].val;
		
		ll mid=l+((r-l)>>1);
		if(pos<=mid)
			return query(tr[rt].lson,l,mid,pos);
		else
			return query(tr[rt].rson,mid+1,r,pos);
	}
	
	Array(){}
	
}arr;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin>>n>>m;
	
	ll x;
	arr.root[0]=++arr.cnt;
	for(int i=1;i<=n;i++){
		cin>>x;
		arr.build_tree(arr.root[0],1,n,i,x);
	}
//	cout<<">>Tree Biult"<<endl;
	ll v,op,loc,key;
	for(int i=1;i<=m;i++){
		cin>>v>>op;
		if(op==1){
			cin>>loc>>key;
			arr.root[++ver]=++arr.cnt;
			arr.update(arr.root[ver],arr.root[v],1,n,loc,key);
		}
		else{
			cin>>loc;
			arr.root[++ver]=arr.root[v];
			cout<<arr.query(arr.root[v],1,n,loc)<<'\n';
		}
	}
	cout.flush();
	return 0;
}
