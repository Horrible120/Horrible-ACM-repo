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

ll ask(ll l,ll r){
	cout<<"xor "<<l<<' '<<r<<endl;
	ll res;
	cin>>res;
	return res;
}

void ans(ll a,ll b,ll c){
	cout<<"ans "<<a<<' '<<b<<' '<<c<<endl;
	return;
}

void solve(){
	ll n,xsum=0,a=0,b=0,c=0,l,r,g;
	cin>>n;
	
	xsum=ask(1,n);	// abc异或和
	
	if(xsum){
		l=1,r=0;
		for(ll i=__lg(n);i>=0;i--)	//倍增，找极大的不包含缺失元素的区间
			if(r+(1ll<<i)<=n)
				if(!ask(l,r+(1ll<<i)))
					r+=1ll<<i;
		a=r+1;
		
		l=a+1,r=a;
		for(ll i=__lg(n-a);i>=0;i--)	//从 a+1 开始，再来一次
			if(r+(1ll<<i)<=n)
				if(!ask(l,r+(1ll<<i)))
					r+=1ll<<i;
		ans(a,r+1,xsum^a^(r+1));
	}
	else{
		g=0;
		while(!a){	//最高位一定是 1,1,0 所以按照最高位来找，第一次遇见的一定有且只有 a
			g++;
			a=ask(1,(1ll<<g)-1);
		}
		
		l=a+1,r=a;
		for(ll i=__lg(n-a);i>=0;i--)
			if(r+(1ll<<i)<=n)
				if(!ask(l,r+(1ll<<i)))
					r+=1ll<<i;
		ans(a,r+1,xsum^a^(r+1));
	}
	
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
