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

void solve(){
	ll n,m,q;
	cin>>n>>m>>q;
	
	vector<ll> a(n+1,0),b(m+1,0);
	vector<pair<ll,ll>> val(n+m+1);
	vector<pair<ll,ll>> k(q+1);
	
	for(ll i=1;i<=n;i++)
		cin>>a[i],
		val[i]=make_pair(a[i],1);
	
	for(ll i=1;i<=m;i++)
		cin>>b[i],
		val[n+i]=make_pair(b[i],0);
	
	for(ll i=1;i<=q;i++)
		cin>>k[i].first,
		k[i].second=i;
	
	sort(val.begin()+1,val.end());
	sort(k.begin()+1,k.end());
	
	
	
	class Gap{
	public:
		ll l,r,itv;
		bool operator <(const Gap &a)const{
			if(this->itv!=a.itv)
				return this->itv<a.itv;
			return this->l<a.l;
		}
		Gap()=default;
		Gap(ll _itv,ll _l,ll _r):l(_l),r(_r),itv(_itv){}
	};
	
	auto gf=[&](auto &&self,vector<ll> &fa,ll x)->ll{
		if(fa[x]==x)
			return x;
		return fa[x]=self(self,fa,fa[x]);
	};
	
	auto dsu_merge=[&](vector<ll> &fa,vector<ll> &siz,vector<ll> &cnt,
	vector<multiset<ll>> &sta,vector<multiset<ll>> &stb,ll x,ll y,ll &ans)->void{
		ll fx=gf(gf,fa,x),fy=gf(gf,fa,y);
		
		if(fx==fy)
			return;
		if(siz[fx]<siz[fy])
			swap(fx,fy);
		
//		while(sta[fy].size()){
//			sta[fx].insert(*sta[fy].begin());
//			sta[fy].erase(sta[fy].begin());
//		}
//		
//		while(stb[fy].size()){
//			stb[fx].insert(*stb[fy].begin());
//			stb[fy].erase(stb[fy].begin());
//		}
		
		
		
		for(auto it:sta[fy])
			sta[fx].insert(it);
		for(auto it:stb[fy])
			stb[fx].insert(it);
		
		while(stb[fx].size()&&sta[fx].size()&&(*stb[fx].rbegin())>(*sta[fx].begin())){
			
			auto bb=*stb[fx].rbegin();
			auto aa=*sta[fx].begin();
			
			ans-=aa;
			ans+=bb;
			
			stb[fx].erase(stb[fx].find(bb));
			sta[fx].erase(sta[fx].begin());
			
			stb[fx].insert(aa);
			sta[fx].insert(bb);
		}
		
		siz[fx]+=siz[fy];
		cnt[fx]+=cnt[fy];
		fa[fy]=fx;
	};
	
	ll ans=0;
	vector<ll> fa(n+m+1,0),siz(n+m+1,0),cnt(n+m+1);
	vector<multiset<ll>> sta(n+m+1);
	vector<multiset<ll>> stb(n+m+1); 
	multiset<Gap> gap;
	
	for(ll i=1;i<=n+m;i++){
		fa[i]=i;
		cnt[i]=val[i].second;
		siz[i]=1;
		
		if(val[i].second)
			ans+=val[i].first,
			sta[i].insert(val[i].first);
		else
			stb[i].insert(val[i].first);
		
		if(i>1)
			gap.insert(Gap(val[i].first-val[i-1].first,i-1,i));
	}
	
	
	
	vector<ll> qans(q+1,0);
	
	for(ll i=1;i<=q;i++){
		
		while(gap.size()&&(*gap.begin()).itv<=k[i].first){
			auto tmp=*gap.begin();
			dsu_merge(fa,siz,cnt,sta,stb,tmp.l,tmp.r,ans);
			gap.erase(gap.begin());
		}
//		OOO
		qans[k[i].second]=ans;
	}
	for(ll i=1;i<=q;i++)
		cout<<qans[i]<<endl;
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
