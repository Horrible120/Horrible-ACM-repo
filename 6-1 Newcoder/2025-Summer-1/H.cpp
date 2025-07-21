#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();    //调试标识
#define H_test(x) println("---> {} <---",x);  //调试输出

using namespace std;
using namespace __gnu_pbds;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")

typedef long long ll;
typedef unsigned int ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

template<typename T>
class H_Fenwick{    //树状数组 类
public:
	ll n;   //总的元素个数
	vector<T> val;    //储存树状数组的数据
	
	H_Fenwick(ll _n):n(_n){ // n 个元素的初始化
		val.assign(n+1,0);
	}
	
	ll lb(ll x) {return x&-x;}  //求 lowbit
	
	T query_Prefsum(ll pos){    //求前缀和
		T res=0;
		while(pos){
			res+=val[pos];
			pos-=lb(pos);
		}
		return res;
	}
	
	T query_Rangesum(ll l,ll r){    //用前缀和求区间和
		return query_Prefsum(r)-query_Prefsum(l-1);
	}
	
	void val_add(ll pos,T key){ //单点修改: 加上key
		while(pos<=n){
			val[pos]+=key;
			pos+=lb(pos);
		}
	}
	
	void val_modify(ll pos,T key){
		val_add(pos,key-query_Rangesum(pos,pos));   //单点修改: 改为key
	}
};

ll head[1<<17],tail[1<<17],sum[1<<17];

void init(){
	for(ll x=0;x<1<<16;x++){
		ull i=x;
		i=(i^(i<<1))&0xffff;
		i=(i^(i<<2))&0xffff;
		i=(i^(i<<4))&0xffff;
		i=(i^(i<<8))&0xffff;
		
//      cout<<x<<' '<<i<<endl;
		
		for(ll j=0;j<16;j++){
			if(i>>j&1){
				head[x]++;
			}else{
				break;
			}
		}
		for(ll j=15;j>=0;j--){
			if(i>>j&1){
				tail[x]++;
			}else{
				break;
			}
		}
		ll cnt=0;
		for(ll j=0;j<16;j++){
			if(i>>j&1){
				cnt++;
			}else{
				cnt=0;
			}
			sum[x]+=cnt;
		}
	}
}

ull get(vector<ull> &val,ll pos){
	if(!(pos&15)){
		return val[pos>>4];
	}else{
		ull low=val[pos>>4]>>(pos&15);
		ull high=val[(pos>>4)+1]<<(16-(pos&15));
		return low|high;
	}
}

void solve(){
	ll n,q;
	cin>>n>>q;
	string ss;
	cin>>ss;
	
	H_Fenwick<ll> fwk(n+18);
	vector<ull> diff(n+18,0),df(n+18,0),v(n+18,0);
	diff[0]|=(ull)(ss[0]-'0');
	fwk.val_add(1,ss[0]-'0');
	
	for(ll i=0;i<n;i++){
		v[i]=ss[i]-'0';
	}
	
	df[0]=v[0];
	for(ll i=1;i<=n;i++){
		df[i]=v[i]^v[i-1];
	}
		
	for(ll i=0;i<n;i++){
		for(ll j=0;j<16;j++){
			diff[i]|=df[i+j]<<j;
		}
	}
	
//	cout<<diff[0]<<endl;
	
	for(ll i=1;i<n;i++){
		fwk.val_add(i+1,(ss[i]-'0')^(ss[i-1]-'0'));
	}
	
	for(ll i=1;i<=q;i++){
		ll op;
		cin>>op;
		if(op==1){
			ll l,r;
			cin>>l>>r;
			
			fwk.val_add(l,1);
			fwk.val_add(r+1,1);
			
			--l,--r;
			
			for(ll j=0;j<16;j++){
				if(l-j>=0) diff[l-j]^=1ull<<j;
				if(r-j+1>=0) diff[r-j+1]^=1ull<<j;
			}
			
//			diff[l>>4]^=1ull<<(l&15);
//			if(r<n-1) diff[(r+1)>>4]^=1ull<<((r+1)&15);
		}else{
			ll l,a,b;
			cin>>l>>a>>b;
			a--,b--;
			
			ull ct=(fwk.query_Prefsum(a)^fwk.query_Prefsum(b))&1;
			ll ans=0,tl=0;
			
			for(ll j=0;j<=(l/16-1)*16;j+=16){
				ull tmp=(((diff[a+j]^diff[b+j]))&0xffff)^ct^1;
				ct=__builtin_popcountll(tmp^1)&1;
				
				ans+=sum[tmp];
				ans-=tl*(tl+1)/2;
				ans-=head[tmp]*(head[tmp]+1)/2;
				ans+=(head[tmp]+tl)*(head[tmp]+tl+1)/2;
				if(tail[tmp]==16) tl+=16;
				else tl=tail[tmp];
				
//				cout<<"!!! "<<tmp<<' '<<sum[tmp]<<' '<<ans<<' '<<tl<<endl;
			}
			if(l%16){
				ull tmp=((diff[a+((l>>4)<<4)]^diff[b+((l>>4)<<4)])&0xffff)^ct^1,cur=0;
				
				for(ll i=0;i<l%16;i++){ 
					cur^=(tmp>>i)&1;
					if(cur){
						tl++;
					}else{
						tl=0;
					}
					ans+=tl;
				}
			}
//			OOO
			cout<<ans<<endl;
		}
	}
	
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
	init();
//  cin >> tt;    //非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
