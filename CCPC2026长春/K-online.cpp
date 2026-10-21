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
	ll n,m,q;
	cin>>n>>m>>q;
	ll lg=1;
	while((1LL<<lg)<=m)
		lg++;

	vector<int> val(m+1);
	vector<array<int,2>> pre(m+1);
	vector<vector<int>> fa(lg,vector<int>(m+1)),stk(2);
	for(ll i=1;i<=m;i++){
		ll op,x;
		cin>>op>>x;
		val[i]=(op?n-x+1:x);
		pre[i]=pre[i-1];
		pre[i][op]=i;

		while(!stk[op].empty()&&val[stk[op][stk[op].size()-1]]<=val[i])
			stk[op].pop_back();
		if(!stk[op].empty())
			fa[0][i]=stk[op][stk[op].size()-1];
		stk[op].emplace_back(i);
	}

	for(ll j=1;j<lg;j++)
		for(ll i=1;i<=m;i++)
			fa[j][i]=fa[j-1][fa[j-1][i]];

	auto get=[&](ll l,ll r)->pair<ll,ll>{
		ll cnt=0,sum=0;
		for(ll op=0;op<2;op++){
			ll cur=pre[r][op];
			if(cur<l)
				continue;
			cnt++;
			for(ll j=lg-1;j>=0;j--)
				if(fa[j][cur]>=l){
					cnt+=1LL<<j;
					cur=fa[j][cur];
				}
			sum+=val[cur];
		}
		return {cnt,sum};
	};

	while(q--){
		ll l,r;
		cin>>l>>r;
		ll low=l,high=r;
		while(low<high){
			ll mid=(low+high+1)/2;
			if(get(mid,r).second>=n)
				low=mid;
			else
				high=mid-1;
		}
		cout<<get(low,r).first<<'\n';
	}
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
