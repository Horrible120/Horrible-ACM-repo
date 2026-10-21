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

const ll INF = 4e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,l,r;
	cin>>n>>l>>r;
	vector<ll> v(4*n+8,0),pres(4*n+8,0),pree(4*n+8,0),preo(n*4+8,0);
	for(ll i=1;i<=n;i++)
		cin>>v[i],pres[i]=pres[i-1]^v[i];
	for(ll i=n+1;i<=2*n+1;i++)
		v[i]=pres[i/2],pres[i]=pres[i-1]^v[i];
	n=2*n+1;
	for(ll i=n+1;i<=2*n;i++)
		v[i]=pres[i/2];
	
	ll p=pres[n];
	
	for(ll i=1;i<=2*n;i++){
		pree[i]=pree[i-1];
		preo[i]=preo[i-1];
		if(i%2==1) preo[i]+=v[i];
		else pree[i]+=v[i];
	}
	
	
	function<ll(ll)> sol=[&](ll k){
		if(k<=n) return v[k];
		if(k/2<=n) return pres[k/2];
		if(n&1){
			if(k/2&1)
				return pres[n];
			else
				return pres[n]^sol(k/2);
		}
		else{
			if(k/2&1)
				return sol(n+1)^pres[n];
			else
				return sol(n+1)^pres[n]^sol(k/2);
		}
	};
	
	function<ll(ll)> sume=[&](ll x){
		if(x<=2*n) return pree[x];
		if(x%4==0){
			return sume(x+1);
		}
		else if(x%4==2){
			return sume(x+3)-sol(x+2);
		}
		else if(x%4==3){
			return sume(x+2)-sol(x+1);
		}
		else if(p==0){
			return sume(x/2)-pree[n]+pree[n*2-1];
		}
		else{
			return x/2-n+1-sume(x/2)+pree[n]+pree[n*2-1];
		}
	};
	
	function<ll(ll)> sumo=[&](ll x){
		if(x<=2*n) return preo[x];
		if(x%4==0){
			return sumo(x+1)-sol(x+1);
		}
		else if(x%4==2){
			return sumo(x+3)-sol(x+3)-p;
		}
		else if(x%4==3){
			return sumo(x+2)-sol(x+2);
		}
		else if(p==0){
			return sume(x/2)-pree[n]+preo[n*2-1];
		}
		else{
			return x/2-n+1-sume(x/2)+pree[n]+preo[n*2-1];
		}
	};
	
	
//	OOO
//	cout<<sol(l)<<endl;
	cout<<sume(r)+sumo(r)-sume(l-1)-sumo(l-1)<<endl;
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
