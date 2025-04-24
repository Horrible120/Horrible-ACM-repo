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
	ll n,mx=0,ans=0,flag=0,sum=0;
	cin>>n;
	vector<ll> v(n+1,0),fa(n+1,0),l(n+1,0),r(n+1,0),pv_odd(n+1,0),pv_even(n+1,0),vis(n+2,0);
	vector<pair<ll,ll>> pos(n+1);
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		pos[i]=make_pair(v[i],i);
		mx=max(mx,v[i]);
		fa[i]=i;
		l[i]=i;
		r[i]=i;
		
	}
	
	for(ll i=1;i<=n;i++){
		pv_odd[i]=pv_odd[i-1];
		pv_even[i]=pv_even[i-1];
		if(v[i]==mx)
			if(i&1)
				pv_odd[i]++;
			else
				pv_even[i]++;
	}
	
	sort(pos.begin()+1,pos.end(),greater<pair<ll,ll>>());
	
	auto GF=[&](auto &&self,ll x)->ll{
		if(fa[x]==x)
			return x;
		return fa[x]=self(self,fa[x]);
	};
	
	auto merge=[&](ll x,ll y){
		ll fx=GF(GF,x),fy=GF(GF,y);
		if(fx==fy) return;
		
		sum-=(r[fx]-l[fx]+2)/2;
		sum-=(r[fy]-l[fy]+2)/2;
		
		if(~(r[fx]-l[fx]+1)&1){
			flag-=max(pv_even[r[fx]]-pv_even[l[fx]-1],pv_odd[r[fx]]-pv_odd[l[fx]-1]);
		}
			
		else{
			if(l[fx]&1){
				flag-=pv_odd[r[fx]]-pv_odd[l[fx]-1];
			}
			else{
				flag-=pv_even[r[fx]]-pv_even[l[fx]-1];
			}
		}
		
		if(~(r[fy]-l[fy]+1)&1){
			flag-=max(pv_even[r[fy]]-pv_even[l[fy]-1],pv_odd[r[fy]]-pv_odd[l[fy]-1]);
		}
		else{
			if(l[fy]&1){
				flag-=pv_odd[r[fy]]-pv_odd[l[fy]-1];
			}
			else{
				flag-=pv_even[r[fy]]-pv_even[l[fy]-1];
			}
		}
		
		l[fx]=min(l[fy],l[fx]);
		r[fx]=max(r[fy],r[fx]);
		
		if(~(r[fx]-l[fx]+1)&1){
			flag+=max(pv_even[r[fx]]-pv_even[l[fx]-1],pv_odd[r[fx]]-pv_odd[l[fx]-1]);
		}
		else{
			if(l[fx]&1){
				flag+=pv_odd[r[fx]]-pv_odd[l[fx]-1];
			}
			else{
				flag+=pv_even[r[fx]]-pv_even[l[fx]-1];
			}
		}
		
		sum+=(r[fx]-l[fx]+2)/2;
		
		fa[fy]=fx;
	};
	
	for(ll i=1;i<=n;i++){
		auto [val,p]=pos[i];
		vis[p]=1;
		if(val==mx) flag++;
		sum++;
		
		if(vis[p-1])
			merge(p,p-1);
		if(vis[p+1])
			merge(p,p+1);
		
//		OOO cout<<p<<' '<<flag<<endl;
		
		ans=max(ans,sum+mx+val+(flag>0?0:-1));
	}
	
//	OOO
	cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
