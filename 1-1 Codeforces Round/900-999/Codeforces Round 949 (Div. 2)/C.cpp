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

void solve(){
	ll n;
	cin>>n;
	vector<ll> v(n+2);
	for(ll i=1;i<=n;i++) cin>>v[i];
	
	ll l,r,flag=1;
	for(ll i=1;i<=n;i++){
		if(v[i]>0) continue;
		l=i;
		while(i<n&&v[i+1]==-1) i++;
		r=i;
		if(l==1){
			for(ll j=r;j>=1;j--)
				v[j]=(v[j+1]>1?v[j+1]/2:2);
		}else if(r==n)
			for(ll j=l;j<=n;j++)
				v[j]=(v[j-1]>1?v[j-1]/2:2);
		else{
			ll x=v[l-1],y=v[r+1],cnt=0;
			while(1){
				if(v[l-1]>v[r+1])
					v[l]=v[l-1]/2,l++;
				else if(v[r+1]>v[l-1])
					v[r]=v[r+1]/2,r--;
				
				if(v[l-1]==v[r+1]) break;
				if(l>r) {
					if(v[l]!=v[r]/2&&v[r]!=v[l]/2) flag=0;
					break;
				}
			}
//			cout<<"!!"<<l<<' '<<r<<endl;
			for(ll j=l;j<=r;j++)
				v[j]=((j-l)&1)?v[j-1]/2:v[j-1]*2;
		}
	}
	for(ll i=1;i<n;i++)
		if(v[i]!=v[i+1]/2&&v[i+1]!=v[i]/2)
			flag=0;
//	OOO
	if(flag)
		for(ll i=1;i<=n;i++) cout<<v[i]<<' ';
	else 
		cout<<-1;
	cout<<endl;
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
