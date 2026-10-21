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

struct node{
	ll id,pos;
};

ll n,k;
vector<vector<ll>> sum;
vector<ll> f,cnt;
vector<node> que;

ll cost(ll l,ll r){
	return (sum[r][r]-sum[l][r]-sum[r][l]+sum[l][l])/2;
}

bool better(ll u,ll v,ll r){
	ll a=f[u]+cost(u,r),b=f[v]+cost(v,r);
	if(a!=b)
		return a<b;
	return cnt[u]<=cnt[v];
}

void check(ll val){
	f[0]=cnt[0]=0;
	ll head=0,tail=0;
	que[0]={0,1};
	for(ll i=1;i<=n;i++){
		while(head<tail&&que[head+1].pos<=i)
			head++;
		ll j=que[head].id;
		f[i]=f[j]+cost(j,i)+val;
		cnt[i]=cnt[j]+1;

		if(i==n)
			continue;
		ll pos=i+1;
		while(head<=tail){
			j=que[tail].id;
			ll l=max(i+1,que[tail].pos),r=n;
			if(better(i,j,l)){
				tail--;
				continue;
			}
			if(!better(i,j,r)){
				pos=n+1;
				break;
			}

			while(l<r){
				ll mid=(l+r)/2;
				if(better(i,j,mid))
					r=mid;
				else
					l=mid+1;
			}
			pos=l;
			break;
		}
		if(pos<=n)
			que[++tail]={i,pos};
	}
}

void solve(){
	cin>>n>>k;
	sum.assign(n+1,vector<ll>(n+1));
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			cin>>sum[i][j];
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		}
	}
	f.resize(n+1);
	cnt.resize(n+1);
	que.resize(n+1);

	ll l=0,r=cost(0,n);
	while(l<r){
		ll mid=(l+r)/2;
		check(mid);
		if(cnt[n]<=k)
			r=mid;
		else
			l=mid+1;
	}
	check(l);
	cout<<f[n]-l*k<<'\n';
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
