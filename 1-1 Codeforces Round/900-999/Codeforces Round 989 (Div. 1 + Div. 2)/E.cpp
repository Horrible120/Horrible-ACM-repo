#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;
vector<ll> fct(21,0);
void init(){
	fct[0]=1;
	
	for(ll i=1;i<=20;i++)
		fct[i]=fct[i-1]*i;
}

void solve(){
	ll n,k;
	cin>>n>>k;
	
	if(n<=20&&k>fct[n]){
		cout<<"NO"<<endl;
		return;
	}
	else if(k==1){
		if(n==1){
			cout<<"YES"<<endl;
			cout<<1<<endl;
			return;
		}
		cout<<"NO"<<endl;
		return;
	}
	else if(k%2==1){
		if(n%2==0||(n<=20&&k>fct[n]-3)){
			cout<<"NO"<<endl;
			return;
		}
	}
	
	auto rvs=[&](vector<ll> &v)->vector<ll>{
		vector<ll> res;
		for(auto it:v)
			res.emplace_back(n+1-it);
		return res;
	};
	
	map<vector<ll>,bool> vis;
	vector<ll> per,rper;
	v2ct<ll> ans;
	
	for(ll i=1;i<=n;i++)
		per.emplace_back(i);
	rper=rvs(per);
	
	if(k%2==0){
		for(ll i=1;i<=k/2;i++){
			while(vis[per]||vis[rper])
				next_permutation(per.begin(),per.end()),
				rper=rvs(per);
			vis[per]=1;
			vis[rper]=1;
			ans.emplace_back(per);
			ans.emplace_back(rper);
		}
	}
	else{
		
		ans.emplace_back(per);
		vis[per]=1;
		vector<ll> tmp1,tmp2;
		tmp1.emplace_back(n/2+1);
		tmp2.emplace_back(n);
		for(ll i=1;i<n;i++){
			tmp1.emplace_back(tmp2.back());
			tmp2.emplace_back(tmp1[i-1]-1);
		}
		ans.emplace_back(tmp1);
		ans.emplace_back(tmp2);
		vis[tmp1]=1;
		vis[tmp2]=1;
		k-=3;
		for(ll i=1;i<=k/2;i++){
			while(vis[per]||vis[rper])
				next_permutation(per.begin(),per.end()),
				rper=rvs(per);
			vis[per]=1;
			vis[rper]=1;
			ans.emplace_back(per);
			ans.emplace_back(rper);
		}
	}
	
	cout<<"YES"<<endl;
	for(auto v:ans)
		for(auto it:v)
			cout<<it<<" \n"[it==v.back()];
	cout.flush();
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	init();
	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
