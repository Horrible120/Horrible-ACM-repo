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

bool check(ll x){
	for(ll i=2;i<min(x,(ll)sqrt(x)+1);i++)
		if(x%i==0) return true;
	return false;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	ll d,s,n;
	cin>>n>>d>>s;
	
	ll top=n/s,lim=d/s;
	
	if(lim==0||top==1) cout<<s<<endl;
	else if(top<=lim+1) cout<<top*s<<endl;
	else if(top>=2*lim) cout<<2*lim*s<<endl;
	else{
		ll cur=0;
		if(top%2==0) cur=top;
		else{
			for(ll i=3;i<min((ll)sqrt(top)+1,top);i++)
				if(top%i==0){
					if((top/i)*(i-1)<=lim){
						cur=top;
						break;
					}
				}
			if(!cur) cur=(top/2)*2;
		}
		cout<<cur*s<<endl;
	}
	
	cout.flush();
	
	return 0;
}
