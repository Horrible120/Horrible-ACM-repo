#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <random>
#include <cstdint>
#include <ctime>
#include <algorithm>
#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;
template <typename T> using v3ct = vector<vector<vector<T>>>;


const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

template <typename T>
class H_bigragh{
public:
	ll n;
	v2ct<T> w;	//边权矩阵
	vector<T> la,lb,slack;	//左侧可行顶标  右侧可行顶标  右侧点的最大“溢出值”
	vector<ll> matcha,matchb,pre;	//左侧点的匹配  右侧点的匹配  当前交错树中右侧点的前一右侧点
	vector<bool> visb;	//vis标记
	
	H_bigragh(ll _n){	//初始化
		n=_n;
		w.assign(n+1,vector<ll>(n+1,-INF));
		la.assign(n+1,0);
		lb.assign(n+1,0);
		matcha.assign(n+1,0);
		matchb.assign(n+1,0);
		visb.assign(n+1,0);
		slack.assign(n+1,INF);
		pre.assign(n+1,0);
	}
	
	void BFS(ll x){	//BFS 增广
		ll y=0,y1=0;	//当前交错树上最新拓展出的右侧节点  当前不在交错树上的“溢出值”最小的右侧节点
		slack.assign(n+1,INF);
		pre.assign(n+1,0);
		
		matchb[y]=x;	//利用下标 0 作为辅助根节点便于操作 避开特判
		
		do{
			ll u=matchb[y],delta=INF;	//当前“溢出值”最小的边对应的左侧节点  当前最小“溢出值”
			visb[y]=true;
			for(ll v=1;v<=n;v++)
				if(!visb[v]){	//如果不在交错树上
					if(slack[v]>la[u]+lb[v]-w[u][v])	//更新“溢出值”
						slack[v]=la[u]+lb[v]-w[u][v],pre[v]=y;
					if(slack[v]<delta)	//更新 y1
						delta=slack[v],y1=v;
				}
			for(ll v=0;v<=n;v++)	//调整可行顶标
				if(visb[v])
					la[matchb[v]]-=delta,lb[v]+=delta;
			else
				slack[v]-=delta;
			y=y1;	//拓展交错树至y1 更新y
		}while(matchb[y]);	//如果还未拓展到某个未匹配节点
		
		while(y)	//对增广路上的边取反
			matchb[y]=matchb[pre[y]],y=pre[y];
		
	}
	
	T KM(){
		la.assign(n+1,0);
		lb.assign(n+1,0);
		matcha.assign(n+1,0);
		matchb.assign(n+1,0);
		
		T res=0;
		
		for(ll i=1;i<=n;i++){
			visb.assign(n+1,0);
			BFS(i);
		}
		
		for(ll i=1;i<=n;i++)	//统计答案
			res+=w[matchb[i]][i],matcha[matchb[i]]=i;
		
		return res;
	}
};

void solve(){
	ll n;
	cin>>n;
	H_bigragh<ll> bgh(n);
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n;j++){
			ll x;
			cin>>x;
			bgh.w[i][j]=-x;
		}
	}
	cout<<-bgh.KM()<<endl;
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
