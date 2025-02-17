#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

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

struct Ps_Trie{	//封装好的可持久化字典树 01 Trie
	
	struct Node{
		ll s[2],key;
		Node(){
			s[0]=s[1]=key=0;
		}
	};
	
	ll cnt=0;
	vector<Node> tree;
	vector<ll> root;
	
	Ps_Trie(){
		cnt=0;
		tree.assign(2,Node());
		root.assign(2,0);
	}
	
	void add_num(ll &rt,ll pre,ll key){	//插入一个新数 版本数增加一
		rt=++cnt;
		ll o=rt;
		
		root.emplace_back(0);
		tree.emplace_back(Node());
		
		for(ll i=31;i>=0;i--){
			
			ll g=(1ll<<i);
			tree[o].key=tree[pre].key+1;
			
			if(key&g){
				tree[o].s[1]=++cnt;
				tree.emplace_back(Node());
				
				tree[o].s[0]=tree[pre].s[0];
				o=tree[o].s[1];
				pre=tree[pre].s[1];
			}
			else{
				tree[o].s[0]=++cnt;
				tree.emplace_back(Node());
				
				tree[o].s[1]=tree[pre].s[1];
				o=tree[o].s[0];
				pre=tree[pre].s[0];
			}
		}
		tree[o].key=tree[pre].key+1;
//		cout<<key<<' '<<tree[o].key<<endl;
	}
	
	ll query_mxor(ll l,ll r,ll key){	//在版本 [l,r] 中查找与 key 异或值最大的数
		if(r<l) swap(l,r);
		ll res=0,o1=root[max(l-1,0ll)],o2=root[r];
		for(ll i=31;i>=0;i--){
			ll g=(1ll<<i);
			ll t=(key&g?1:0);
			if(tree[tree[o2].s[!t]].key-tree[tree[o1].s[!t]].key > 0){
				res+=g;
				o2=tree[o2].s[!t];
				o1=tree[o1].s[!t];
			}
			else{
				o2=tree[o2].s[t];
				o1=tree[o1].s[t];
			}
		}
//		cout<<endl;
		return res;
	}
};

void solve(){
	ll n,m,cnt=0,xorsum=0;
	cin>>n>>m;
	
	Ps_Trie tr=Ps_Trie();
	vector<ll> v(1);
	
	for(ll i=1;i<=n;i++){
		ll x;
		cin>>x;
		
		xorsum^=x;
		cnt++;
		
		tr.add_num(tr.root[i],tr.root[i-1],xorsum);
	}
	for(ll i=1;i<=m;i++){
		char op;
		ll l,r,x;
		cin>>op;
		if(op=='A'){
			cin>>x;
			
			cnt++;
			xorsum^=x;
			
			tr.add_num(tr.root[cnt],tr.root[cnt-1],xorsum);
		}
		else{
			cin>>l>>r>>x;
			if(l==1) cout<<max(x^xorsum,tr.query_mxor(l-1,r-1,x^xorsum))<<endl;
			else cout<<tr.query_mxor(l-1,r-1,x^xorsum)<<endl;
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
	}
	
	cout.flush();
	return 0;
}
