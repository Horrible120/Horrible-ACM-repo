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

const ll INF = 1e15, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void solve(){
	ll n,q,ans=0;
	cin>>n>>q;
	
	vector<ll> v(q+1,0);
	
	for(ll i=1;i<=q;i++) cin>>v[i];
	
	vector<array<ll,3>> st(q+1,{{}});
	vector<vector<vector<ll>>> dp(q+1,vector<vector<ll>>(q+1,vector<ll>(q+1,INF))),min_val(3,vector<vector<ll>>(q+1,vector<ll>(q+1,INF)));
	vector<array<ll,2>> tsk(q+1,{{}});
	
	st[0]={{1,1,1}};
	tsk[0]={1,1};
	
	for(ll i=1;i<=q;i++){
		ll op;
		cin>>op;
		st[i]=st[i-1];
		if(op==2){
			ll x;
			cin>>x;
			st[i][x-1]^=1;
		}else{
			ll x,y;
			cin>>x>>y;
			ans+=abs(x-y)*v[i];
			tsk[i]={{x,y}};
		}
	}
	
	for(ll i=0;i<3;i++){
		for(ll j=1;j<=q;j++){
			if(st[j][i]) min_val[i][j][j]=v[j];
			for(ll k=j+1;k<=q;k++){
				if(st[k][i]) min_val[i][j][k]=min(v[k],min_val[i][j][k-1]);
				else min_val[i][j][k]=min_val[i][j][k-1];
			}
			min_val[i][0][j]=min_val[i][1][j];
		}
	}
	
	ll lst=0;
	
	dp[0][0][0]=0;
	
	for(ll i=1;i<=q;i++){
		if(tsk[i][0]){
			
//			cout<<">>> "<<i<<endl;
			
			for(ll j=0;j<=lst;j++){
				for(ll k=0;k<=lst;k++){
					
					ll a=tsk[lst][1],b=tsk[j][1],c=tsk[k][1],d=tsk[i][0];
					ll ad=abs(a-d),bd=abs(b-d),cd=abs(c-d);
					
					if(st[i][0]){
						dp[i][j][k]=min(dp[i][j][k],dp[lst][j][k]+min_val[0][lst][i]*ad);
						dp[i][lst][k]=min(dp[i][lst][k],dp[j][lst][k]+min_val[0][j][i]*bd);
						dp[i][k][lst]=min(dp[i][k][lst],dp[j][k][lst]+min_val[0][j][i]*bd);
					}
					
					if(st[i][1]){
						dp[lst][i][k]=min(dp[lst][i][k],dp[lst][j][k]+min_val[1][j][i]*bd);
						dp[j][i][k]=min(dp[j][i][k],dp[j][lst][k]+min_val[1][lst][i]*ad);
						dp[j][i][lst]=min(dp[j][i][lst],dp[j][k][lst]+min_val[1][k][i]*cd);
					}
					
					if(st[i][2]){
						dp[lst][j][i]=min(dp[lst][j][i],dp[lst][j][k]+min_val[2][k][i]*cd);
						dp[j][lst][i]=min(dp[j][lst][i],dp[j][lst][k]+min_val[2][k][i]*cd);
						dp[j][k][i]=min(dp[j][k][i],dp[j][k][lst]+min_val[2][lst][i]*ad);
					}
				}
			}
			
			lst=i;
		}else{
			
		}
	}
	
	ll aans=INF;
	
//	OOO
	
	for(ll i=0;i<=lst;i++){
		for(ll j=0;j<=lst;j++){
			aans=min(aans,dp[i][j][lst]);
			aans=min(aans,dp[i][lst][j]);
			aans=min(aans,dp[lst][i][j]);
		}
	}
	
	cout<<ans+aans<<endl;
	
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



