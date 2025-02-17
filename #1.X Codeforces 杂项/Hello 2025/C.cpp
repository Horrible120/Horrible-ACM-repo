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
	ll l,r;
	ll a=0,b=0,c=0,flag=1;
	ll fa=0,fb=0,fc=0;
	cin>>l>>r;
	ll cur=__lg(r);
//	cout<<cur<<endl;
	
	while(cur>=0){
		if(l/(1<<cur)==r/(1<<cur)){
			a+=(1<<cur)*((l/(1<<cur))%2);
			b+=(1<<cur)*((l/(1<<cur))%2);
			c+=(1<<cur)*((l/(1<<cur))%2);
		}
		else if(flag&&l/(1<<cur)==r/(1<<cur)-1){
			if(r-(1<<cur)*(r/(1<<cur))+1>=(1<<cur)*(r/(1<<cur))-l){
				a+=(1<<cur);
				b+=(1<<cur);
				fc=1;
			}
			else{
				a+=(1<<cur);
				fb=fc=1;
			}
			flag=0;
		}
		else{
			a+=(1<<cur)*fa;
			b+=(1<<cur)*fb;
			c+=(1<<cur)*fc;
		}
		cur--;
	}
	
	if(fa==fb) a+=1;
	else c-=1;
	
//	OOO
	cout<<a<<' '<<b<<' '<<c<<endl;
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
