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
	ll n;
	cin>>n;
	vector<ll> v(n+1,0);
	
	for(ll i=1;i<=n;i++)
		cin>>v[i];
	
	ll l=1,r=n/2+1;
	ll lbd=n,rbd=1;
	while(l<r){
		ll mid=(l+r+1)>>1;
		multiset<ll,greater<ll>> ls,rs;
		ll ld=1,rd=n;
		ll cur=mid;
		
		while(cur&&ld<=n){
			ls.insert(v[ld]);
			ld++;
			while(ls.size()&&(*ls.begin())>=cur&&cur>0){
				ls.erase(ls.begin());
				cur--;
			}
		}
		
		cur=mid;
		while(cur&&rd>=1){
			rs.insert(v[rd]);
			rd--;
			while(rs.size()&&(*rs.begin())>=cur&&cur>0){
				rs.erase(rs.begin());
				cur--;
			}
		}
		
		if(ld-1<rd+1){
			l=mid;
			lbd=ld-1;
			rbd=rd+1;
		}
		else
			r=mid-1;
	}
	
//	OOO
//	cout<<l<<' '<<lbd<<' '<<rbd<<endl;
	
	ll ans=0;
	
	multiset<pair<ll,ll>,greater<pair<ll,ll>>> sl,sr;
	multiset<ll> xl;
	multiset<ll,greater<ll>> xr;
	
	for(ll i=1;i<=lbd;i++)
		sl.insert(make_pair(v[i],i));
	for(ll i=l;i>=1;i--){
		while(sl.size()&&(*sl.begin()).first>=i){
			xl.insert((*sl.begin()).second);
			sl.erase(sl.begin());
		}
		ans-=*xl.begin();
		xl.erase(xl.begin());
	}
	
	for(ll i=n;i>=rbd;i--)
		sr.insert(make_pair(v[i],i));
	for(ll i=l;i>=1;i--){
		while(sr.size()&&(*sr.begin()).first>=i){
			xr.insert((*sr.begin()).second);
			sr.erase(sr.begin());
		}
		ans+=*xr.begin();
		xr.erase(xr.begin());
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
