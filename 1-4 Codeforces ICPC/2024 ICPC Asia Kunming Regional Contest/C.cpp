#include <bits/stdc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

using namespace std;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;


const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

void solve(){
	ll n,k,cnt=0,tmp=0;
	cin>>n>>k;
	
	ll tar=n;
	while(tar>k){
		ll md=(tar-1)/k+1;	//当前每轮淘汰的人数
		ll tm=max(1ll,(tar-(md-1)*k+md-1)/md);	//这种轮次要进行多少轮
		cnt+=tm;
		tar-=tm*md;
	}
//	cout<<"!!!"<<tar<<' '<<cnt<<endl;
	while(cnt){
		ll md=(tar-1)/(k-1)+1;
		if(md==1){
			ll tmp=min(k-tar,cnt);
			tar+=tmp;
			cnt-=tmp;
			continue;
		}
		ll tm=min(cnt,max(1ll,(md*(k-1)-tar)/md+1));
		tar+=tm*md;
		cnt-=tm;
	}
//	OOO
	cout<<tar<<endl;
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
