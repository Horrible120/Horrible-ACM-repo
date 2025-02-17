#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

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

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

struct Edge{
	ll u,v,w,col;
	bool operator<(const Edge &_t){
		if(w!=_t.w) return w<_t.w;
		return col<_t.col;
	}
};

ll get_fa(vector<ll> &fa,ll x){
	if(fa[x]==x) return x;
	return fa[x]=get_fa(fa,fa[x]);
}

void joint(vector<ll> &fa,ll x,ll y){
	ll fax=get_fa(fa,x),fay=get_fa(fa,y);
	if(fax==fay) return;
	fa[fax]=fay;
}

void solve(){
	ll n,m,s,need,ans=0,scnt=0;
	cin>>n>>m>>s>>need;
	
	vector<Edge> eg(m+1);
	for(ll i=1;i<=m;i++){
		cin>>eg[i].u>>eg[i].v>>eg[i].w;
		if(eg[i].u==s||eg[i].v==s) eg[i].col=0,scnt++;
		else eg[i].col=1;
	}
	
	
//	sort(eg.begin()+1,eg.end());
	
	auto check=[&](ll x)->ll{
//		cout<<"!!!"<<endl;
		vector<ll> fa(n+1);
		for(ll i=1;i<=n;i++) fa[i]=i;
		for(ll i=1;i<=m;i++)
			if(eg[i].col==0)
				eg[i].w+=x;
		
		sort(eg.begin()+1,eg.end());
		ll cnt=0,cur=0,flag=0,res=0;
		while(cnt<n-1){
			Edge e=eg[++cur];
			if(get_fa(fa,e.u)==get_fa(fa,e.v)) continue;
			joint(fa,e.u,e.v);
			res+=e.w;
			flag+=(e.col+1)%2;
			cnt++;
		}
		for(ll i=1;i<=m;i++)
			if(eg[i].col==0)
				eg[i].w-=x;
		if(flag>=need) ans=res-need*x;
		return flag;
	};
	
	if(check(1000000)>need||check(-1000000)<need){
		cout<<"Impossible"<<endl;
		return;
	}
	
	ll l=-30000,r=30000;
	while(l<r){
		
		ll mid=(l+r+1)/2;
		ll flag=check(mid);
		
//		cout<<"!!!"<<endl;
		
		if(flag>=need) l=mid;
		else r=mid-1;
	}
	
//	OOO
	cout<<ans<<endl;
	
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
