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
	ll n,ans=0;
	cin>>n;
	vector<ll> a(n+1);
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		ans+=a[i];
	}
	sort(a.begin()+1,a.end(),greater<ll>());

	std::priority_queue<ll,vector<ll>,greater<ll>> q;
	ll s=0;
	for(ll i=1;i<=n;){
		ll j=i;
		while(j<=n&&a[j]==a[i])
			j++;
		ll v=a[i],c=j-i;
		ll t=min(c,s-2*(ll)q.size()),r=c-t;
		vector<ll> b;
		for(ll k=0;k<t;k++)
			b.emplace_back(v);

		while(r>=2&&!q.empty()){
			ll d=q.top();
			q.pop();
			ll x=max(d,v);
			b.emplace_back(x);
			if(2*v-x>0)
				b.emplace_back(2*v-x);
			r-=2;
		}
		if(r==1&&!q.empty()){
			b.emplace_back(max(q.top(),v));
			q.pop();
		}

		for(ll k=0;k<(ll)b.size();k++)
			q.emplace(b[k]);
		s+=c;
		i=j;
	}

	while(!q.empty()){
		ans-=q.top();
		q.pop();
	}
	cout<<ans<<'\n';
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
