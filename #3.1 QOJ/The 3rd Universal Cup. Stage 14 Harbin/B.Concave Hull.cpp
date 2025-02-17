#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识
#define CY cout<<"YES"<<endl;	//输出宏
#define CN cout<<"NO"<<endl;	//输出宏

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 2e18, Mod = 1e9+7;

ll tt=1;

template <typename T>
class H_Convex_Hull{
public:
	class Node{
	public:
		T x,y;
		Node():x(0),y(0){}
		Node(T _x,T _y):x(_x),y(_y){}
		friend bool operator<(const Node &_a,const Node &_b){
			if(_a.x!=_b.x) return _a.x<_b.x;
			else return _a.y<_b.y;
		}
	};
	
	ll n;
	T Convex_Perieter,Convex_S;
	vector<Node> node;
	vector<ll> Convex_Hull,incvx;
	
	H_Convex_Hull(){
		n=0;
		node.assign(1,Node());
	}
	
	void add_node(T _x,T _y){
		n++;
		node.emplace_back(Node(_x,_y));
	}
	
	static T crossP(Node _a,Node _b,Node _c){	//返回 ab ac 的叉积 若大于零则前者在后者顺时针方向
		return (_b.x-_a.x)*(_c.y-_a.y)-(_c.x-_a.x)*(_b.y-_a.y);
	}
	
	T node_dist(Node _a,Node _b){
		return sqrt(pow(_a.x-_b.x,2)+pow(_a.y-_b.y,2));
	}
	
	void get_Convex_Hull(){
		Convex_Hull.assign(0,T());
		if(node.size()==1) return;
		ll top=0;
		vector<ll> stk(2*n+1,0);
		incvx.assign(n+1,0);
		sort(node.begin()+1,node.end());
		stk[++top]=1;
		for(ll i=2;i<=n;i++){
			while(top>=2&&crossP(node[stk[top-1]],node[stk[top]],node[i])<0)
				incvx[stk[top--]]=0;
			stk[++top]=i;
			incvx[i]=true;
		}
		incvx[1]=false;
		ll tmp=top;
		for(ll i=n-1;i>=1;i--){
			if(!incvx[i]){
				while(top>tmp&&crossP(node[stk[top-1]],node[stk[top]],node[i])<0)
					incvx[stk[top--]]=0;
				stk[++top]=i;
				incvx[i]=true;
			}
		}
		incvx[1]=1;
		for(ll i=1;i<=top;i++)
			Convex_Hull.emplace_back(stk[i]);
	}
	
	void get_Convex_Perieter(){
		get_Convex_Hull();
		Convex_Perieter=0;
		for(ll i=1;i<Convex_Hull.size();i++)
			Convex_Perieter+=node_dist(node[Convex_Hull[i-1]],node[Convex_Hull[i]]);
	}
	
	void get_Convex_S(){
		get_Convex_Hull();
		Convex_S=0;
		for(ll i=1;i<Convex_Hull.size();i++)
			Convex_S+=crossP(Node(0,0),node[Convex_Hull[i-1]],node[Convex_Hull[i]]);
		Convex_S=abs(Convex_S);
	}
};

void solve(){
	ll n;
	cin>>n;
	H_Convex_Hull<ll> h1,h2;
	for(ll i=1;i<=n;i++){
		ll x,y;
		cin>>x>>y;
		h1.add_node(x,y);
	}
	h1.get_Convex_S();
//	cout<<h1.Convex_S<<endl;
	for(ll i=1;i<=n;i++)
		if(!h1.incvx[i]) h2.add_node(h1.node[i].x,h1.node[i].y);
	h2.get_Convex_Hull();
	
//	cout<<h2.Convex_Hull.size()<<endl;
//	for(auto it:h2.Convex_Hull)
//		cout<<h2.node[it].x<<' '<<h2.node[it].y<<endl;
	if(h2.node.size()==1){
		cout<<-1<<endl;
		return;
	}
	
	ll pos=0;
	ll ans=INF;
	for(ll i=1;i<h1.Convex_Hull.size();i++){
		vector<ll> &ch1=h1.Convex_Hull,&ch2=h2.Convex_Hull;
		ll vis=0;
		while(	abs(H_Convex_Hull<ll>::crossP(h1.node[ch1[i-1]],h1.node[ch1[i]],h2.node[ch2[(pos+1)%ch2.size()]]))<
				abs(H_Convex_Hull<ll>::crossP(h1.node[ch1[i-1]],h1.node[ch1[i]],h2.node[ch2[pos]]))){
			vis++;
			pos=(pos+1)%ch2.size();
			if(vis>n) break;
		}
		ans=min(ans,abs(H_Convex_Hull<ll>::crossP(h1.node[ch1[i-1]],h1.node[ch1[i]],h2.node[ch2[pos]])));
//		cout<<h1.node[ch1[i-1]].x<<' '<<h1.node[ch1[i-1]].y<<endl;
//		cout<<h1.node[ch1[i]].x<<' '<<h1.node[ch1[i]].y<<endl;
//		cout<<h2.node[ch2[pos]].x<<' '<<h2.node[ch2[pos]].y<<endl;
	}
	cout<<h1.Convex_S-ans<<endl;
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
/*
2
6
-2 0
1-2
5 2
0 4
1 2
3 1
4
0 0
1 0
0 1
1 1
*/
