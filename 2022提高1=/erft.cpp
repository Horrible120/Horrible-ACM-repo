#include<queue>
#include<cstdio>
#include<iostream>
using namespace std;

struct Edge {
	int u,v,f;
	int next;
} edge[1000010];

int n,m,e,s,t;
int first[500010],tot;
int dis[500010];
bool book[500010];
long long ans;

queue <int> q;

void add_edge(int a,int b,int z,int i) {
	if(first[a])
		edge[i].next=first[a];
	first[a]=i;
	edge[i].u=a;
	edge[i].v=b;
	edge[i].f=z;
}

bool BFS(int root) {

	for(int i=0; i<=t; ++i) {
		book[i]=false;
		dis[i]=0;
	}

	q.push(root);
	book[root]=true;
	dis[root]=1;

	int x,cur;

	while(!q.empty()) {
		x=q.front();
		q.pop();
		cur=first[x];

		while(cur) {
			if(!book[edge[cur].v] && edge[cur].f>0) {
				book[edge[cur].v]=true;
				q.push(edge[cur].v);
				dis[edge[cur].v]=dis[x]+1;
			}
			cur=edge[cur].next;
		}
	}

	if(dis[t]>0)
		return 1;
	else
		return 0;
}

int DFS(int x,int flow) {
	if(x==t || flow==0)
		return flow;

	int a=0;
	int cur=first[x];
	while(cur) {
		if( dis[edge[cur].v]==dis[x]+1 && edge[cur].f>0 )
			if(a=DFS( edge[cur].v , min( flow , edge[cur].f ) )) {
				edge[cur].f-=a;
				edge[cur^1].f+=a;
				return a;
			}
		cur=edge[cur].next;
	}
	dis[x]=0;
	return 0;
}

int main() {
	int x,y,z;

	scanf("%d%d%d",&n,&m,&e);

	s=0;
	t=n+m+1;
	tot=1;

	for(int i=1; i<=e; i++) {
		scanf("%d%d",&x,&y);
		add_edge(x,n+y,1,++tot);
		add_edge(n+y,x,0,++tot);
	}

	for(int i=1; i<=n; i++) {
		add_edge(0,i,1,++tot);
		add_edge(i,0,0,++tot);
	}

	for(int i=1; i<=m; i++) {
		add_edge(n+i,n+m+1,1,++tot);
		add_edge(n+m+1,n+i,0,++tot);
	}

	while(BFS(s)) {
		int a;
		while(a=DFS(s,999999999))
			ans+=a;
	}

	printf("%lld\n",ans);

	return 0;
}
