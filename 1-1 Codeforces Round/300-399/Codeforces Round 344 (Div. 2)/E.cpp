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

struct Node{
	ll x,y;

	Node(ll _x,ll _y):x(_x),y(_y){}

	ll val(ll t) const{
		return y-x*t;
	}
};

ll cross(Node p,Node q,Node r){
	return (q.x-p.x)*(r.y-p.y)-(q.y-p.y)*(r.x-p.x);
}

void solve(){
	ll n,sum=0;
	cin>>n;
	vector<ll> val(n+1),pre(n+1);
	for(ll i=1;i<=n;i++){
		cin>>val[i];
		pre[i]=pre[i-1]+val[i];
		sum+=i*val[i];
	}

	vector<Node> hull;
	hull.reserve(n+1);
	for(ll i=0;i<=n;i++){
		Node cur(i,pre[i]);
		while(hull.size()>=2&&cross(hull[hull.size()-2],hull[hull.size()-1],cur)<=0)
			hull.pop_back();
		hull.emplace_back(cur);
	}

	ll ans=sum;
	for(ll i=1;i<=n;i++){
		ll l=0,r=(ll)hull.size()-1;
		while(l<r){
			ll mid=(l+r)/2;
			if(hull[mid].val(val[i])>=hull[mid+1].val(val[i]))
				l=mid+1;
			else
				r=mid;
		}
		ans=max(ans,sum+pre[i-1]-(i-1)*val[i]-hull[l].val(val[i]));
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
