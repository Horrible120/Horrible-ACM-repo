#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
using pll = pair<ll,ll>;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

const int L=45;
const int NG=-1e9;

using arr = array<char,5>;

bool ok(const arr &s,int ban){
	for(int i=0;i<5;i++)
		if(i!=ban&&s[i])
			return 1;
	return 0;
}

void merge_arr(const arr &a,const arr &b,const arr &c,arr &res){
	if(ok(a,0)&&ok(b,0)&&ok(c,0))
		res[0]=1;
	
	if(ok(a,1)&&ok(b,1)&&ok(c,1)&&(a[0]||b[0]||c[0]))
		res[1]=1;
	
	if(ok(a,2)&&ok(b,2)&&ok(c,2)){
		if(a[0]&&(b[1]||c[1])) res[2]=1;
		if(b[0]&&(a[1]||c[1])) res[2]=1;
		if(c[0]&&(a[1]||b[1])) res[2]=1;
	}
	
	if(a[0]&&b[1]&&c[2]) res[3]=1;
	if(a[0]&&b[2]&&c[1]) res[3]=1;
	if(a[1]&&b[0]&&c[2]) res[3]=1;
	if(a[1]&&b[2]&&c[0]) res[3]=1;
	if(a[2]&&b[0]&&c[1]) res[3]=1;
	if(a[2]&&b[1]&&c[0]) res[3]=1;
}

void solve(){
	ll n;
	cin>>n;
	
	vector<ll> v(n+2,0);
	vector<int> a(n+2,0);
	
	for(ll i=1;i<=n;i++){
		cin>>v[i];
		a[i]=(v[i]<=3?v[i]:4);
	}
	
	vector<array<arr,L>> f(n+2);
	
	for(ll i=0;i<=n+1;i++){
		for(int j=0;j<L;j++){
			for(int k=0;k<5;k++){
				f[i][j][k]=0;
			}
		}
	}
	
	for(ll i=1;i<=n;i++)
		f[i][1][a[i]]=1;
	
	for(int len=3;len<L;len+=2){
		for(ll l=1;l+len-1<=n;l++){
			for(int x=1;x<=len-2;x+=2){
				for(int y=1;x+y<=len-1;y+=2){
					int z=len-x-y;
					if(z<=0||z%2==0) continue;
					
					merge_arr(f[l][x],f[l+x][y],f[l+x+y][z],f[l][len]);
				}
			}
		}
	}
	
	vector<array<int,4>> dp(n+1);
	
	for(ll i=0;i<=n;i++){
		for(int j=0;j<4;j++){
			dp[i][j]=NG;
		}
	}
	
	for(int j=0;j<4;j++)
		dp[0][j]=0;
	
	array<array<int,4>,2> bst;
	
	for(int i=0;i<2;i++){
		for(int j=0;j<4;j++){
			bst[i][j]=NG;
		}
	}
	
	for(ll i=1;i<=n;i++){
		ll p=i-L;
		if(p>=0){
			for(int j=0;j<4;j++)
				bst[p&1][j]=max(bst[p&1][j],dp[p][j]);
		}
		
		array<int,4> cur;
		for(int j=0;j<4;j++)
			cur[j]=NG;
		
		for(int len=1;len<L&&len<=i;len+=2){
			ll j=i-len;
			for(int x=0;x<4;x++){
				if(f[j+1][len][x]&&dp[j][x]>NG/2)
					cur[x]=max(cur[x],dp[j][x]+1);
			}
		}
		
		ll need=1-(i&1);
		for(int x=0;x<4;x++){
			if(bst[need][x]>NG/2)
				cur[x]=max(cur[x],bst[need][x]+1);
		}
		
		dp[i][0]=cur[0];
		for(int x=1;x<4;x++)
			dp[i][x]=max(dp[i][x-1],cur[x]);
	}
	
	vector<char> suf(n+2,0);
	suf[n+1]=1;
	for(ll i=n;i>=1;i--)
		suf[i]=(i==n||(v[i]<=v[i+1]&&suf[i+1]));
	
	int ans=1e9;
	
	for(ll i=0;i<=n;i++){
		if(!suf[i+1]) continue;
		
		int keep=0;
		
		if(i){
			int lim=3;
			if(i<n&&v[i+1]<=3)
				lim=v[i+1];
			
			keep=dp[i][lim];
			if(keep<0) continue;
		}
		
		ll del=i-keep;
		if(del%2==0)
			ans=min(ans,(int)(del/2));
	}
	
	if(ans==1e9)
		cout<<-1<<endl;
	else
		cout<<ans<<endl;
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
//	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
	}
	
	cout.flush();
	return 0;
}
