#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	
	while ( tt-- ) {
		ll n,k,ans;
		cin>>n>>k;
		vector<ll> a(n+1),b(n+1);
		oset<pair<ll,ll>> s;
		for(ll i=1;i<=n;i++) cin>>a[i],s.insert(make_pair(a[i],i));
		for(ll i=1;i<=n;i++) cin>>b[i];
		
		ans=(*s.rbegin()).first+(*s.find_by_order(n/2-1)).first;
		
		for(ll i=1;i<=n;i++){
			if(b[i]){
				s.erase(make_pair(a[i],i));
				ans=max(ans,a[i]+(*s.find_by_order(n/2-1)).first+k);
				s.insert(make_pair(a[i],i));
			}
		}
		
		ll l=1,r=2e9,mid,hf=(n+1)/2;
		while(l<=r){
			mid=(l+r)/2;
			ll cur=k,cnt=0;
			for(ll i=n-2;i>=0&&cnt<hf;i--){
				ll x=(*s.find_by_order(i)).first,y=(*s.find_by_order(i)).second;
				if(x<mid&&b[y])
					if(mid-x<=cur){
						cur-=mid-x;
						++cnt;
					}
					else break;
				else if(x>=mid)
					++cnt;
			}
			if(cnt>=hf){
				ans=max(ans,mid+(*s.rbegin()).first);
				l=mid+1;
			}
			else
				r=mid-1;
		}
//		OOO
//		cout<<l<<' '<<r<<' ';
		
		cout<<ans<<endl;
	}
	
	cout.flush();
	
	return 0;
}
