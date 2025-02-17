#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>

using namespace std;

typedef long long ll;
typedef uint64_t ull;

ll tot,cnt,ans;

ll n,m,k;

struct Node
{
	ll fa,fir;
}node[1010];

struct Edge
{
	ll u,v,w,next;
	bool operator<(const Edge &e) const
	{
		return w<e.w;
	}
}edge[20010];

bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}

void add_edge(ll u,ll v,ll w)
{
	edge[++tot].u=u;
	edge[tot].v=v;
	edge[tot].w=w;
	edge[tot].next=node[u].fir;
	node[u].fir=tot;
	
	
}

ll get_fa(ll x)
{
	if(node[x].fa==x) return x;
	return node[x].fa=get_fa(node[x].fa);
}

void join(ll x,ll y)
{
	if(get_fa(x)==get_fa(y))
		return;
	else
		node[get_fa(y)].fa=get_fa(x);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>n>>m>>k;
	
	int u,v,w;
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		add_edge(u,v,w);
	}
	
	for(int i=1;i<=n;i++)
		node[i].fa=i;
	
	sort(edge+1,edge+m+1);
	
	//for(int i=1;i<=m&&cnt<n-k;i++)
	//	cout<<edge[i].w<<endl;
	
	for(int i=1;i<=m&&cnt<n-k;i++)
	{
		Edge e=edge[i];
		
		if(get_fa(e.u)!=get_fa(e.v))
		{
			join(e.u,e.v);
			cnt++;
			ans+=e.w;
		}
			
		//cout<<e.u<<' '<<e.v<<' '<<get_fa(1)<<' '<<get_fa(2)<<' '<<get_fa(3)<<endl;
	}
	
	cout<<ans<<endl;
	
	return 0;
}
/*
3 3 1
3 2 2
2 1 1
3 1 1
*/

