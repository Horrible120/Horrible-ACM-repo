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
	ll n;
	cin>>n;
	vector<ll> a(n+1,0),b(n+1,0);
	string sa,sb;
	ll suma=0,sumb=0;
	cin>>sa>>sb;
	for(ll i=1;i<=n;i++){
		a[i]=sa[i-1]-'0';
		b[i]=sb[i-1]-'0';
		suma+=a[i];
		sumb+=b[i];
	}
	
	if(suma==0||sumb==0){
		if(suma==sumb){
			cout<<0<<endl;
		}else{
			cout<<-1<<endl;
		}
		return;
	}
	
	vector<ll> ans;
	
	ll al=1,bl=1,ar=n,br=n;
	while(!a[al]) al++;
	while(!b[bl]) bl++;
	while(!a[ar]) ar--;
	while(!b[br]) br--;
	vector<ll> tmp;
	
	auto mov=[&](ll k){
		ans.emplace_back(k);
		tmp=a;
		for(ll i=1;i<=n;i++){
			if(i+k>0&&i+k<=n){
				a[i]^=tmp[i+k];
			}
		}
	};
	
	if(al<bl){
		if(ar<bl){
			mov(ar-bl);
			ar=bl;
		}
		for(ll i=bl;i>=1;i--){
			if(a[i]!=b[i]){
				mov(ar-i);
			}
		}
	}else if(al>bl){
		mov(al-bl);
	}
	
	for(ll i=bl+1;i<=n;i++){
		if(a[i]!=b[i]){
			mov(bl-i);
		}
	}
	
	cout<<ans.size()<<endl;
	for(auto it:ans){
		cout<<it<<' ';
	}
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
