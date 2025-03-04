#include <bits/extc++.h>
#define OOO cout<<">>>>";	//调试标识

using namespace std;
using namespace __gnu_pbds;

mt19937_64 rnd( time( 0 ) );
typedef long long ll;
typedef uint64_t ull;
template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 1e18, Mod = 1e9+7;

ll tt=1;

const ll maxn=5e3+5;
ll a[maxn],siz[maxn],dep[maxn];
ll b[maxn],ans;
ll n;
vector<ll>e[maxn];
void dfs(ll x){//预处理出 b 值
	siz[x]=1;
	b[x]=-a[x];
	for(auto v:e[x]){
		dep[v]=dep[x]+1;//标 dep 便于计算代价
		b[x]+=a[v];
		dfs(v);
		siz[x]+=siz[v];
	}
	if(siz[x]==1)b[x]=1ll<<31;//叶子的 b 值为正无穷
}
vector<ll>work(ll x){//返回的是点集
	vector<ll>lst;//自己的点集
	for(auto v:e[x]){
		vector<ll>res=work(v);
		vector<ll>tmp;
		ll l=0,r=0,len1=lst.size(),len2=res.size();
		while(l<len1||r<len2){//归并
			if(l==len1)tmp.push_back(res[r++]);
			else if(r==len2)tmp.push_back(lst[l++]);
			else if(dep[lst[l]]>dep[res[r]])tmp.push_back(lst[l++]);
			else tmp.push_back(res[r++]);
		}
		lst.swap(tmp);
	}
	if(b[x]>0)lst.push_back(x);//b>0 则放入自身
	else if(b[x]<0){
		ll p=lst.size()-1;//不用验空，b<0 其必有儿子，有儿子必有后代为叶子
		while(b[x]<0){
			ll it=lst[p];
			ll sum=min(-b[x],b[it]);//要么直接填满，要么把这个用完
			b[it]-=sum,b[x]+=sum;
			ans+=sum*(dep[it]-dep[x]);//代价
			if(b[it]==0)p--,lst.pop_back();//用完扔掉不然单调性没法保证
		}
	}
	return lst;//自身点集向上合并
}
void solve(){
	cin>>n;
	ans=0;//清多测
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		e[i].clear();//这里好一点的写法是用 tmp.swap(e[i]) 彻底释放空间
		//但由于题目保证了数据总和，抢时间就不写太麻烦了
	}
	for(ll i=2;i<=n;i++){
		ll x;
		cin>>x;
		e[x].push_back(i);}
	dfs(1);
	work(1);
	cout<<ans<<endl;
	return ;
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
