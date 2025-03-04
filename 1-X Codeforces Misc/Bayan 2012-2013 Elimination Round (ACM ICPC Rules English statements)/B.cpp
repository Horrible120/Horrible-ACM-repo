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
		ll s[2],key,num;
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
	
	void add_num(ll &rt,ll pre,ll key,ll id){	//插入一个新数 版本数增加一
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
		tree[o].num=id;
//		cout<<key<<' '<<tree[o].key<<endl;
	}
	
	ll query_mxor(ll l,ll r,ll key){	//在版本 [l,r] 中查找与 key 异或值最大的数 *的下标
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
//		cout<<tree[o2].num<<endl;
		return tree[o2].num;
	}
};

struct Elm{
	ll s,t,l,r,key;
	bool operator < (const Elm &a) const {
		return key>a.key;
	}
};

void solve(){
	ll n,k,ans=0;
	cin>>n>>k;
	
	Ps_Trie tr=Ps_Trie();
	vector<ll> v(n+1);
	multiset<Elm> hp;
	
	for(ll i=1;i<=n;i++){
		cin>>v[i],v[i]^=v[i-1];
		tr.add_num(tr.root[i],tr.root[i-1],v[i],i);
	}
	
	function<void(ll,ll,ll)> cstr=[&](ll s,ll l,ll r){
		
		if(l>r) return;
		
		Elm tmp={};
		tmp.s=s;
		tmp.l=l;
		tmp.r=r;
		tmp.t=tr.query_mxor(l,r,v[s-1]);
		tmp.key=v[tmp.t]^v[s-1];
		
		hp.insert(tmp);
	};
	
	for(ll i=1;i<=n;i++)
		cstr(i,i,n);
	
	while(k--){
		Elm tmp=*hp.begin();
		hp.erase(hp.begin());
		ans+=tmp.key;
		
		cstr(tmp.s,tmp.l,tmp.t-1);
		cstr(tmp.s,tmp.t+1,tmp.r);
	}
	cout<<ans<<endl;
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
