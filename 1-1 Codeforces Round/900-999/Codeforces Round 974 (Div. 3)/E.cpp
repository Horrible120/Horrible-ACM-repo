#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node
{
	int num;
	int head;
	long long val1=0x3f,val2=0x3f;
	bool vis1=0,vis2=0;
	int 
	int h=1;
};

struct Edge
{
	int u,v,w;
	int next;
	
};

struct cmp1
{
	bool operator()(Node a, Node b)
	{
		return a.val1 > b.val1;
	}
            
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int t=0;
	
	cin>>t;
	
	while(t--)
	{
		int n,m,h;
		cin>>n>>m>>h;
		
		vector<Node> node(n+1);
		vector<Edge> edge(2*m+1); 
		
		for(int i=1;i<=m;i++)
		{
			int u,v,w;
			cin>>u>>v>>w;
			
			if(node[u].head)
				edge[(i<<1)-1].next=node[u].head;
			node[u].head=(i<<1)-1;
			edge[(i<<1)-1].u=u;
			edge[(i<<1)-1].v=v;
			edge[(i<<1)-1].w=w;
			
			if(node[v].head)
				edge[i<<1].next=node[u].head;
			node[v].head=i<<1;
			edge[i<<1].u=v;
			edge[i<<1].v=u;
			edge[i<<1].w=w;
		} 
		
		for(int i=1;i<=h;i++)
			node[i].num=i;
		
		for(int i=1;i<=h;i++)
		{
			int hnod;
			cin>>hnod;
			node[hnod].h=2;
		}
		
		priority_queue<Node,vector<Node>,cmp1> heap1;
		priority_queue<Node,vector<Node>,cmp1> heap2;
		
		node[1].val1=0;
		heap1.push(node[1]);
		while(!heap1.empty())
		{
			Node cur=node[heap1.top().num];
			heap1.pop();
			if(cur.vis1) continue;
			
			cur.vis1=1;
			
			
			Edge e=edge[cur.head];
			
			while(e.u)
			{
				int v=e.v;
				int w=e.w;
				if(node[v].val1>cur.val1+w/cur.h)
				{
					node[v].val1=cur.val1+w/cur.h;
					
					node[v].h=cur.h;
					
					heap1.push(node[v]);
				}
				e=edge[e.next];
			}
		}
	}
	
	
	
	return 0;
}
