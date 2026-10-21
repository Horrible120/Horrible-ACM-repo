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
	string s[4];
	
	cout<<"0 0"<<endl;
	getline(cin,s[0]);
	if(s[0].back()=='!') return;
	
	
	cout<<"1 1"<<endl;
	getline(cin,s[1]);
	if(s[1].back()=='!') return;
	
	cout<<"0 0"<<endl;
	getline(cin,s[2]);
	
	if(s[2]==s[1]){
		cout<<"0 1"<<endl;
		getline(cin,s[0]);
		if(s[0].back()=='!') return;
		
		cout<<"1 0"<<endl;
		getline(cin,s[1]);
		if(s[1].back()=='!') return;
	}
	
	map<string,ll> res;
	
	res[s[1]]=0;
	res[s[2]]=1;
	
	ll xl=0,xr=1000000,yl=0,yr=1000000;
	
	while(xl<xr||yl<yr){
		ll xm=xl+xr>>1;
		ll ym=yl+yr>>1;
		
		string s;
		
		ll flag[2];
		
		cout<<xl<<' '<<yl<<endl;
		getline(cin,s);
		if(s.back()=='!') return;
		
		cout<<xr<<' '<<yl<<endl;
		getline(cin,s);
		if(s.back()=='!') return;
		else if(res.count(s)){
			flag[0]=res[s];
		}else flag[0]=2;
		
		cout<<xr<<' '<<yr<<endl;
		getline(cin,s);
		if(s.back()=='!') return;
		else if(res.count(s)){
			flag[1]=res[s];
		}else flag[1]=2;
		
		if(flag[0]==0){
			xl=(xl+xr+1)/2;
		}else if(flag[0]==1){
			xr=(xl+xr-1)/2;
		}else{
			xl=xr=(xr+xl)/2;
		}
		
		if(flag[1]==0){
			yl=(yl+yr+1)/2;
		}else if(flag[1]==1){
			yr=(yl+yr-1)/2;
		}else{
			yl=yr=(yr+yl)/2;
		}
	}
	
	cout<<xl<<' '<<yl<<endl;
	getline(cin,s[0]);
	if(s[0].back()=='!') return;
	
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
