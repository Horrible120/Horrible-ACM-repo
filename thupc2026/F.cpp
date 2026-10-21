#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,q,cnt=0;
	cin>>n>>q;
	
	vector<ll> op(q+1,0),x(q+1,0),c(q+1,0);
	vector<ll> nd(q+1,0);
	
	for(ll i=1;i<=q;i++){
		cin>>op[i];
		if(op[i]==1){
			cin>>x[i]>>c[i];
			nd[++cnt]=x[i];
		}else{
			cin>>x[i];
			nd[++cnt]=x[i];
		}
	}
	
	sort(nd.begin()+1,nd.begin()+cnt+1);
	
	auto get_fa=[&](ll y)->ll{
		if(y==1ll) return 0ll;
		ll res=sqrtl((y-1ll)*2ll);
		if(y>res*(res+1ll)/2ll+1ll) res++;
		return res;
	};
	
	auto get_siz=[&](ll l,ll r)->pair<ll,ll>{
		if(l>=1500000000ll||l*(l-1ll)/2ll+2ll>n) return make_pair(-1ll,-1ll);
		else if(r>=1500000000ll) return make_pair(l*(l-1ll)/2ll+2ll,n);
		else return make_pair(l*(l-1ll)/2ll+2ll,min(r*(r+1ll)/2ll+1ll,n));
	};
	
	auto get_asiz=[&](ll x)->ll{
		ll res=0;
		pair<ll,ll> seq=make_pair(x,x);
		while(seq.second!=-1){
			res+=seq.second-seq.first+1ll;
			seq=get_siz(seq.first,seq.second);
		}
		return res;
	};
	
//	for(ll i=1;i<=3;i++){
//		ll xx;
//		cin>>xx;
//		cout<<get_fa(xx)<<' '<<get_siz(xx,xx).first<<' '<<get_siz(xx,xx).second<<' '<<get_asiz(xx)<<endl;
//	}
	
	ll tot=0;
	map<ll,ll> ord;
	vector<ll> fa(10*cnt+1,0),oor(10*cnt+1,0),sval(10*cnt+1,0);
	
	ord[1ll]=++tot;
	
	for(ll i=1;i<=cnt;i++){
		ll cur=nd[i];
		if(ord[cur]) continue;
		ord[cur]=++tot;
		ll ffa=get_fa(cur);
		while(cur>1&&(!ord[ffa])){
			ord[ffa]=++tot;
			fa[ord[cur]]=tot;
			cur=ffa;
			ffa=get_fa(cur);
		}
		if(cur>1){
			fa[ord[cur]]=ord[ffa];
		}
	}
	
	fa[1]=0;
	
//	for(ll i=1;i<=n;i++){
//		cout<<i<<": "<<fa[ord[i]]<<' '<<ord[i]<<endl;
//	}
	
	for(ll i=1;i<=q;i++){
		if(op[i]==1){
			ll cur=ord[x[i]],xior=0;
			
			ll ans1=0,ans2=0;
			
			while(cur){
				xior|=oor[cur];
				cur=fa[cur];
			}
			
			cur=ord[x[i]];
			
			if(get_asiz(x[i])&1ll){
				ans1=(((~xior)&(sval[cur]))|xior);
				ans2=(((~(xior|c[i]))&(sval[cur]))|(xior|c[i]));
			}else{
				ans1=((~xior)&(sval[cur]));
				ans2=((~(xior|c[i]))&(sval[cur]));
			}
			
			oor[cur]|=c[i];
			
			ll tmp=(ans1^ans2);
			cur=fa[cur];
			
			while(cur){
				sval[cur]^=tmp;
				cur=fa[cur];
			}
		}else{
			ll cur=ord[x[i]],xior=0;
			ll ans=sval[cur];
			
			while(cur){
				xior|=oor[cur];
				cur=fa[cur];
			}
			
			cur=ord[x[i]];
			
			if(get_asiz(x[i])&1ll){
				ans=(((~xior)&(sval[cur]))|xior);
			}else{
				ans=((~xior)&(sval[cur]));
			}
			cout<<ans<<endl;
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
