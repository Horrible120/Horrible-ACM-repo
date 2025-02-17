// 洛谷 P5459 [BJOI2016] 回转寿司
// 权值线段树  初学练习
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

typedef long long ll;
typedef uint64_t ull;

const ll INF=1e10;

ll cnt;
ll n,l,r;
ll a[100010],pre[100010];
ll Root;

struct Node{
	ll lson,rson,num;
	Node (){}
}node[3000010];

void add_node(ll &root,ll l,ll r,ll k){
	ll mid=l+((r-l)>>1);
	if(!root)
		root=++cnt;
		
//	cout<<"KKK"<<endl;
	node[root].num++;
	if(l==r)
		return;
	if(k>mid)
		add_node(node[root].rson,mid+1,r,k);
	else
		add_node(node[root].lson,l,mid,k);
}

ll get_num(ll root,ll l,ll r,ll s,ll t){
	if(r<s||l>t||(!root))
		return 0;
	ll mid=l+((r-l)>>1),num=0;
	if(l>=s&&r<=t)
		return node[root].num;
	if(mid>=s)
		num+=get_num(node[root].lson,l,mid,s,t);
	if(mid<t)
		num+=get_num(node[root].rson,mid+1,r,s,t);
	return num;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>l>>r;
	
	for(int i=1;i<=n;i++){
		cin>>a[i];
		pre[i]=pre[i-1]+a[i];
	}
	
	ll ans=0;
	
	Root=++cnt;
	add_node(Root,-INF,INF,0);
	for(int i=1;i<=n;i++){
		ans+=get_num(Root,-INF,INF,pre[i]-r,pre[i]-l);
		add_node(Root,-INF,INF,pre[i]);
		
	}
	cout<<ans<<endl;
	

	return 0;
}

