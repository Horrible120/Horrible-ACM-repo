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

const ll INF = 1e18, Mod = 1e9+7;

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
	vector<ll> Convex_Hull;
	
	H_Convex_Hull(){
		n=0;
		node.assign(1,Node());
	}
	
	void add_node(T _x,T _y){
		n++;
		node.emplace_back(Node(_x,_y));
	}
	
	T crossP(Node _a,Node _b,Node _c){	//返回 ab ac 的叉积 若大于零则前者在后者顺时针方向
		return (_b.x-_a.x)*(_c.y-_a.y)-(_c.x-_a.x)*(_b.y-_a.y);
	}
	
	T node_dist(Node _a,Node _b){
		return sqrt(pow(_a.x-_b.x,2)+pow(_a.y-_b.y,2));
	}
	
	void get_Convex_Hull(){
		Convex_Hull.assign(0,T());
		if(node.size()==1) return;
		ll top=0;
		vector<ll> stk(2*n+1,0),instk(n+1);
		sort(node.begin()+1,node.end());
		stk[++top]=1;
		for(ll i=2;i<=n;i++){
			while(top>=2&&crossP(node[stk[top-1]],node[stk[top]],node[i])<=0)
				instk[stk[top--]]=0;
			stk[++top]=i;
			instk[i]=true;
		}
		ll tmp=top;
		for(ll i=n-1;i>=1;i--){
			if(!instk[i]){
				while(top>tmp&&crossP(node[stk[top-1]],node[stk[top]],node[i])<=0)
					instk[stk[top--]]=0;
				stk[++top]=i;
				instk[i]=true;
			}
		}
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
		Convex_S=abs(Convex_S)/2;
	}
};

void solve(){
	
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
