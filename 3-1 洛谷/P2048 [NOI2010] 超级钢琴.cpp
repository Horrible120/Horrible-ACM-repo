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

struct Elm{
	ll s,t,l,r,key;
	bool operator < (const Elm &a) const {
		return key>a.key;
	}
};

void solve(){
	ll n,k,L,R,ans=0;
	cin>>n>>k>>L>>R;
	
	vector<ll> v(n+1,0);
	v2ct<ll> st(n+1,vector<ll>(21,0));
	multiset<Elm> hp;
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		v[i]+=v[i-1];
		st[i][0]=i;
	}
	
	for(ll k=1;k<=20;k++)
		for(ll i=1;i<=n;i++){
			ll g=min(n,i+(1<<(k-1)));
			st[i][k]=(v[st[i][k-1]]>=v[st[g][k-1]]?st[i][k-1]:st[g][k-1]);
		}
			
	
	function<ll(ll,ll)> get_max =[&](ll l,ll r){
		ll g=__lg(r-l+1);
		ll w=(g==-1?0:(1<<g));
		if(g==-1) g++;
		return v[st[l][g]]>=v[st[r-w+1][g]]?st[l][g]:st[r-w+1][g];
	};
	
	function<void(ll,ll,ll)> cstr=[&](ll s,ll l,ll r){
		
		if(l>r) return;
		
		Elm tmp={};
		tmp.s=s;
		tmp.l=l;
		tmp.r=r;
		tmp.t=get_max(tmp.l,tmp.r);
		tmp.key=v[tmp.t]-v[s-1];
		
		hp.insert(tmp);
	};
	
	for(ll i=1;i<=n&&i+L-1<=n;i++)
		cstr(i,i+L-1,min(n,i+R-1));
	
	for(ll i=1;i<=k;i++){
		Elm cur=*hp.begin();
		hp.erase(hp.begin());
		ans+=cur.key;
		
		cstr(cur.s,cur.l,cur.t-1);
		cstr(cur.s,cur.t+1,cur.r);
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
