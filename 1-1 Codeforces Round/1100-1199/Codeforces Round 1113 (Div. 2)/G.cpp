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
	ll n,m,s;
	cin>>n>>m>>s;
	vector<ll> cost(n+1),a(m+1),b(m+1);
	ll mn=INF,g=0;
	for(ll i=1;i<=n;i++){
		cin>>cost[i];
		mn=min(mn,cost[i]);
		g=gcd(g,cost[i]);
	}
	for(ll i=1;i<=m;i++)
		cin>>a[i]>>b[i];

	if(mn>=a[1]){
		for(ll i=1;i<=s;i++)
			cout<<"NO\n";
		return;
	}

	const ll N=125005;
	bitset<N> can,win,pre,loss;
	ll top=max(s,a[m]);
	can[0]=1;
	for(ll i=1;i<=n;i++)
		can[cost[i]]=1;
	for(ll i=1;i<=top;i++)
		if(can[i])
			can|=can<<i;

	ll pos=0,lim=s+1;
	g=gcd(g,b[m]);
	win[0]=1;
	pre[0]=1;
	for(ll i=1;i<=top;i++){
		while(pos<m&&a[pos+1]<=i)
			pos++;

		if(can[i]){
			ll d=i-b[pos];
			g=gcd(g,abs(d));
			if(d<0)
				lim=min(lim,i);
			else if(d>0)
				loss[d]=1;
		}

		if(i<lim){
			pre<<=1;
			win[i]=(pre&loss).any();
			pre[0]=win[i];
		}
	}

	for(ll i=1;i<=s;i++){
		bool ans=i<lim?win[i]:i%g==0;
		cout<<(ans?"YES":"NO")<<'\n';
	}
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	//cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
