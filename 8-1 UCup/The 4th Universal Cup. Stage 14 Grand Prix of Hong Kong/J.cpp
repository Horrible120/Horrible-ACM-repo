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
	vector<ll> lim(4),sum(4),pos(4,1),ord{0,1,2,3};
	vector<vector<ll>> a(4,vector<ll>(1));
	cin>>n>>lim[1]>>lim[2]>>lim[3];
	for(ll i=1;i<=n;i++){
		ll p,c;
		cin>>p>>c;
		a[p].emplace_back(c);
		sum[p]+=c;
	}
	ll t;
	cin>>t;

	for(ll i=1;i<=3;i++)
		sort(a[i].begin()+1,a[i].end());
	sort(ord.begin()+1,ord.end(),[&](ll x,ll y){
		return lim[x]<lim[y];
	});

	ll now=0,ans=0;
	for(ll i=1;i<=n;i++){
		ll who=0,best=INF;
		for(ll j=1;j<=3;j++){
			if(pos[j]==(ll)a[j].size())
				continue;
			ll cost=a[j][pos[j]];
			if(now+cost>lim[j])
				continue;

			bool ok=true;
			ll cur=now+cost;
			for(ll k=1;k<=3;k++){
				ll p=ord[k];
				ll rem=sum[p]-(p==j?cost:0);
				if(!rem)
					continue;
				cur+=rem;
				if(cur>lim[p]){
					ok=false;
					break;
				}
			}
			if(ok&&cost<best){
				who=j;
				best=cost;
			}
		}

		if(!who){
			cout<<"NO\n";
			return;
		}
		now+=best;
		ans+=now;
		sum[who]-=best;
		pos[who]++;
	}
	cout<<(ans<t?"YES":"NO")<<'\n';
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	cin >> tt;	//非多组测试数据时注释掉即可

	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();

	return 0;
}
