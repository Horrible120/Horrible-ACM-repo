#include <bits/extc++.h>
#define OOO cout<<">>>>";cout.flush();	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("inline")

typedef long long ll;
typedef uint64_t ull;
using i128 = __int128;
using pll = pair<ll,ll>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 998244353;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
	if(!b) { d = a; x = 1; y = 0; }
	else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}
ll inv(ll a){
	ll d,x,y;
	exgcd(a%Mod,Mod,d,x,y);
	return d == 1 ? (x+Mod)%Mod : -1;
}

ll dt[13]={-1,31,28,31,30,31,30,31,31,30,31,30,31};
const ll i24=inv(24);

void solve(){	//日期统一包含本位 年份统一不包含
	ll n,ans=0;
	cin>>n;
	string s;
	cin>>s;
	
	if(n<8){
		cout<<0<<endl;
		return;
	}
	
	vector<ll> v(n+1,0),dtcnt(n+2,0),zcnt(n+2,0),rcnt(n+2,0);	//字符串 合法日期计数（不计0229） 前缀 0 计数（排除0000） 前缀闰年计数
	vector<vector<ll>> cnt0229(n+2,vector<ll>(5,0));	//后缀0229 必包含本位
	for(ll i=0;i<n;i++){
		v[i+1]=s[i]-'0';
	}
	
	for(ll i=1;i<=n;i++){
		zcnt[i]=zcnt[i-1];
		if(v[i]==0){
			zcnt[i]++;
		}
	}
	
	for(ll i=n;i>=1;i--){	//统计后缀0229（
		cnt0229[i]=cnt0229[i+1];
		cnt0229[i][4]=0;
		if(v[i]==0){
			cnt0229[i][4]=cnt0229[i][3];	//可以继承所有229后缀
		}
		if(v[i]==2){
			cnt0229[i][3]=(cnt0229[i][3]+cnt0229[i][2])%Mod;
			cnt0229[i][2]=(cnt0229[i][2]+cnt0229[i][1])%Mod;
		}
		if(v[i]==9){
			cnt0229[i][1]++;
		}
	}
	
	for(ll i=400;i<10000;i+=400){	//统计前缀 xx00 闰年
		vector<ll> tmp(5,0);
		for(ll j=1;j<=n;j++){
			if(v[j]==i%10){
				tmp[4]=(tmp[4]+tmp[3])%Mod;
			}
			if(v[j]==i/10%10){
				tmp[3]=(tmp[3]+tmp[2])%Mod;
			}
			if(v[j]==i/100%10){
				tmp[2]=(tmp[2]+tmp[1])%Mod;
			}
			if(v[j]==i/1000%10){
				tmp[1]++;
			}
			rcnt[j]=(rcnt[j]+tmp[4])%Mod;
		}
	}
	
	for(ll i=4;i<100;i+=4){		//枚举末两位 统计前缀 非xx00 闰年
		vector<ll> tmp(5,0);
		for(ll j=1;j<=n;j++){
		
			if(v[j]==i%10){	
				tmp[4]=(tmp[4]+tmp[3])%Mod;
			}
			if(v[j]==i/10%10){
				tmp[3]=(tmp[3]+tmp[2])%Mod;
			}
			
			tmp[2]=(tmp[2]+tmp[1])%Mod;	//前两位是任取的
			tmp[1]++;
			
			rcnt[j]=(rcnt[j]+tmp[4])%Mod;
		}
	}
	
	for(ll i=4;i<=n-4;i++){	//统计闰年0229数量
		ans=(ans+rcnt[i]*cnt0229[i+1][4])%Mod;
	}
	
	for(ll i=0;i<=1231;i++){	//统计后缀合法日期
		ll m=i/100;
		ll d=i%100;
		if(d>dt[m]) continue;
		vector<ll> tmp(4,0);
		for(ll j=n;j>=1;j--){
			if(v[j]==i/1000%10){
				dtcnt[j]=(dtcnt[j]+tmp[3])%Mod;
			}
			if(v[j]==i/100%10){
				tmp[3]=(tmp[3]+tmp[2])%Mod;
			}
			if(v[j]==i/10%10){
				tmp[2]=(tmp[2]+tmp[1])%Mod;
			}
			if(v[j]==i%10){
				tmp[1]++;
			}
		}
	}
	
	auto C4=[](ll x){
		return x*(x-1)*(x-2)%Mod*(x-3)%Mod*i24%Mod;
	};
	
	for(ll i=5;i<=n-3;i++){	//统计非0229的组合（排除0000作为年份的情况）
		ans=(ans+dtcnt[i]*((C4(i-1)-C4(zcnt[i-1]))%Mod+Mod))%Mod;
	}
//	OOO
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
