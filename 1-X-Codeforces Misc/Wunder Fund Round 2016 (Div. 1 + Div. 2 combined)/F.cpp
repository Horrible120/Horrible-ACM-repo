#include <bits/extc++.h>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n;
	cin>>n;
	vector<ll> a(n+1),b(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		a[i]+=a[i-1];
	}
	for(ll i=1;i<=n;i++){
		cin>>b[i];
		b[i]+=b[i-1];
	}

	bool rev=a[n]>b[n];
	if(rev)
		swap(a,b);
	vector<pair<ll,ll>> pos(n,{-1,-1});
	pos[0]={0,0};

	ll j=0;
	for(ll i=1;i<=n;i++){
		while(b[j]<a[i])
			j++;
		ll dif=b[j]-a[i];
		if(pos[dif].first!=-1){
			ll la=pos[dif].first+1,ra=i;
			ll lb=pos[dif].second+1,rb=j;
			if(rev){
				swap(la,lb);
				swap(ra,rb);
			}

			cout<<ra-la+1<<'\n';
			for(ll k=la;k<=ra;k++)
				cout<<k<<' ';
			cout<<'\n';
			cout<<rb-lb+1<<'\n';
			for(ll k=lb;k<=rb;k++)
				cout<<k<<' ';
			cout<<'\n';
			return;
		}
		pos[dif]={i,j};
	}
	cout<<-1<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

//	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
