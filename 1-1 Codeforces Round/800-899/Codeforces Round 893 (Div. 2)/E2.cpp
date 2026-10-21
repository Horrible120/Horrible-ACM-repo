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
	
	ll n=1e6;
	ll pnt=0,top=0;
	
	vector<ll> pos(n+1,0),str(n+1,0);
	
	vector<ll> pref(n+1,0),stk(n+1,0);
	
	vector<pair<ll&,ll>> cback;
	
	for(ll i=1;i<=q;i++){
		string op;
		cin>>op;
		
		
		if(op[0]=='+'){
			stk[++top]=cback.size();
			
			ll x;
			cin>>x;
			cback.emplace_back(pnt,pnt);
			++pnt;
			
			if(str[pnt]&&pos[str[pnt]]==pnt){
				cback.emplace_back(pos[str[pnt]],pos[str[pnt]]);
				pos[str[pnt]]=0;
			}
			
			cback.emplace_back(str[pnt],str[pnt]);
			str[pnt]=x;
			
			if(pos[x]==0||pos[x]>pnt){
				cback.emplace_back(pos[x],pos[x]);
				pos[x]=pnt;
			}
			
			cback.emplace_back(pref[pnt],pref[pnt]);
			pref[pnt]=pref[pnt-1]+(pos[x]==pnt);
			
		}else if(op[0]=='-'){
			stk[++top]=cback.size();
			
			ll k;
			cin>>k;
			
			cback.emplace_back(pnt,pnt);
			pnt-=k;
		}else if(op[0]=='!'){
			while(cback.size()>stk[top]){
				cback.back().first=cback.back().second;
				cback.pop_back();
			}
			top--;
		}else{
//			OOO
//			cout<<pnt<<endl;
			cout<<pref[pnt]<<endl;
		}
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
