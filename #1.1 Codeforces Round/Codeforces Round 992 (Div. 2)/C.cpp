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

ll tt;

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;
	vector<ll> jc(21);
	jc[0]=1;
	for(ll i=1;i<=20;i++)
		jc[i]=jc[i-1]*i;
	
	while ( tt-- ) {
		ll n,k;
		cin>>n>>k;
		vector<ll> v(n+1),mp(n+1),pre(n+1),sub(n+1),ans(n+1);
		
//		pre[1]=1;
//		for(ll i=2;i<=n;i++) pre[i]=(v[i]<v[pre[i-1]]?i:pre[i-1]);
//		sub[n]=n;
//		for(ll i=n;i>=1;i--) sub[i]=(v[i]<v[sub[i+1]]?i:sub[i+1]);
		
		if(n<20&&k>jc[n]){
			cout<<-1<<endl;
			continue;
		}
		
		oset<pair<ll,ll>> s;
		s.insert(make_pair(n,1));
		k--;
		for(ll i=1;i<=n;i++){
			ll od=((n-i)<20)?(k/jc[n-i]):0;
			if(od) k-=od*jc[n-i];
			od++;
			ll st,len,coo;
			for(ll i=0;i<s.size();i++){
				cout.flush();
				auto [x,y]=*s.find_by_order(i);
//				cout<<x<<' '<<y<<endl;
				if(od<=x){
					st=y;
					len=x;
					s.erase(s.find_by_order(i));
					break;
				}
				else od-=x;
			}
			if(od%2) coo=st+od/2;
			else coo=st+len-1-od/2;
			cout<<"!"<<coo<<' '<<st<<' '<<len<<' '<<od<<endl;
			ans[coo]=i;
			if(coo-st>1) s.insert(make_pair(coo-st+1,st));
			if(st+len-1-coo>1) s.insert(make_pair(st+len-coo,coo+1));
		}
		for(ll i=1;i<=n;i++)
			cout<<ans[i]<<' ';
		cout<<endl;
	}
	
	cout.flush();
	
	return 0;
}
