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
	if(n&(n-1)){
		cout<<n<<" 1\n"<<string(n,'2')<<'\n';
		return;
	}

	ll d=n-1,all=(1LL<<d)-1;
	vector<ll> ids(all+1,-1),lev;
	for(ll x=1;x<=all;x++){
		if(ids[x]!=-1)
			continue;
		ll id=lev.size(),y=x;
		lev.emplace_back(__builtin_ctzll(x));
		do{
			ids[y]=id;
			y=(y^(y<<1))&all;
		}while(y!=x);
	}

	ll cnt=lev.size(),len=(cnt+63)/64;
	vector<ull> trans(d*cnt*len);
	for(ll j=0;j<d;j++)
		for(ll x=1;x<=all;x++){
			ll y=x^(1LL<<j);
			if(!y)
				continue;
			ll id=ids[y],pos=(j*cnt+ids[x])*len;
			trans[pos+id/64]|=1ULL<<(id%64);
		}

	vector<string> ans;
	if(n>2)
		for(ll j=0;(1LL<<j)<n;j++){
			string str(n,'0');
			for(ll i=0;i<n;i++)
				if(i>>j&1)
					str[i]='2';
			ans.emplace_back(str);
		}

	vector<ull> cur(len),nxt(len);
	cur[ids[1]/64]|=1ULL<<(ids[1]%64);
	while(true){
		ll top=-1;
		for(ll i=0;i<cnt;i++)
			if(cur[i/64]>>(i%64)&1)
				top=max(top,lev[i]);
		if(top==-1)
			break;

		string str(n,'0');
		for(ll i=top;;i=(i-1)&top){
			str[i]='1';
			if(!i)
				break;
		}
		ans.emplace_back(str);

		fill(nxt.begin(),nxt.end(),0);
		for(ll i=0;i<len;i++){
			ull bits=cur[i];
			while(bits){
				ll id=i*64+__builtin_ctzll(bits);
				bits&=bits-1;
				ll pos=(top*cnt+id)*len;
				for(ll j=0;j<len;j++)
					nxt[j]|=trans[pos+j];
			}
		}
		cur.swap(nxt);
	}

	cout<<n/2<<' '<<ans.size()<<'\n';
	for(ll i=0;i<(ll)ans.size();i++)
		cout<<ans[i]<<'\n';
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
