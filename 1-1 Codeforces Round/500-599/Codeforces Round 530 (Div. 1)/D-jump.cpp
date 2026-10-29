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
	ll q;
	cin>>q;
	vector<pair<char,ll>> ops(q);
	vector<ll> val;
	val.reserve(q);
	for(ll i=0;i<q;i++){
		cin>>ops[i].first>>ops[i].second;
		val.emplace_back(ops[i].second);
	}

	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	ll m=val.size();
	vector<ll> num(m+1),sum(m+1);
	ll top=1;
	while((top<<1)<=m)
		top<<=1;

	auto add=[&](ll p,ll v,ll x)->void{
		for(;p<=m;p+=p&-p){
			num[p]+=v;
			sum[p]+=v*x;
		}
	};
	auto ask=[&](ll p)->pair<ll,ll>{
		ll cnt=0,tot=0;
		for(;p;p-=p&-p){
			cnt+=num[p];
			tot+=sum[p];
		}
		return {cnt,tot};
	};
	auto kth=[&](ll k)->ll{
		ll p=0;
		for(ll d=top;d;d>>=1){
			ll v=p+d;
			if(v<=m&&num[v]<k){
				p=v;
				k-=num[v];
			}
		}
		return p+1;
	};

	ll cnt=0;
	for(ll i=0;i<q;i++){
		auto [op,x]=ops[i];
		ll id=lower_bound(val.begin(),val.end(),x)-val.begin()+1;
		ll delta=op=='+'?1:-1;
		add(id,delta,x);
		cnt+=delta;

		ll cut=0;
		if(cnt){
			ll pre=val[kth(1)-1],used=1;
			cut=1;
			while(used<cnt){
				ll pos=upper_bound(val.begin(),val.end(),2*pre)-val.begin();
				auto [now,tot]=ask(pos);
				if(now>used){
					used=now;
					pre=tot;
				}else{
					pre+=val[kth(used+1)-1];
					used++;
					cut++;
				}
			}
		}

		cout<<cnt-cut<<'\n';
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
