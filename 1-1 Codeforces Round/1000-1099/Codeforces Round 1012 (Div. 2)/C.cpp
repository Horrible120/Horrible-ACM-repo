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
ll px[5]={0,1,1,2,2},py[5]={0,1,2,1,2};

struct Tb{
	ll x,y;
	ll lst;
	bool operator<(const Tb &a)const{
		if(x+y!=a.x+a.y)
			return x+y<a.x+a.y;
		else if(x!=a.x)
			return x<a.x;
		return y<a.y;
	}
};

void solve(){
	ll n;
	cin>>n;
	
	set<Tb> s0,s1,s4;
	
	for(ll i=0;i<=2*sqrt(n)+2;i++)
		for(ll j=0;j<=2*sqrt(n)+2;j++){
			Tb tmp;
			tmp.x=i;
			tmp.y=j;
			tmp.lst=1;
			s0.insert(tmp);
		}
			
	for(ll i=1;i<=n;i++){
		ll ty;
		cin>>ty;
		if(ty==0){
			auto t1=*s0.begin();
//			cout<<"S0 "<<t1.x<<' '<<t1.y<<endl;
			s0.erase(s0.begin());
			cout<<t1.x*3+px[t1.lst]<<' '<<t1.y*3+py[t1.lst]<<'\n';
			t1.lst++;
			s1.insert(t1);
		}
		else{
			auto t1=*s0.begin();
			if(!s1.empty()){
				auto t2=*s1.begin();
				if(t2.x+t2.y<t1.x+t1.y)
					swap (t2,t1);
			}
			if(!s4.empty()){
				auto t2=*s4.begin();
				if(t1.lst==1)
					if(t2.x+t2.y<t1.x+t1.y-1)
						swap (t2,t1);
				if(t1.lst>1){
					if(t2.x+t2.y<t1.x+t1.y-1)
						swap (t2,t1);
					else if(t2.x+t2.y==t1.x+t1.y-1)
						if(t2.x<t1.x||(t2.x==t1.x&&t1.lst==3))
							swap(t2,t1);
				}
					
			}
			
			cout<<t1.x*3+px[t1.lst]<<' '<<t1.y*3+py[t1.lst]<<'\n';
			
			if(t1.lst==1){
				s0.erase(s0.begin());
				t1.lst++;
				s1.insert(t1);
			}	
			else if(t1.lst==4){
				s4.erase(s4.begin());
			}
			else{
				s1.erase(s1.begin());
				t1.lst++;
				if(t1.lst==4)
					s4.insert(t1);
				else
					s1.insert(t1);
			}
		}
	}
	cout.flush();
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
