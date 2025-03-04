#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Edge
{
	int u,v,next;
}edge[200010];

struct Node
{
	int head;
	int dis=0;
}node[200010];

int n,m,tot,ans;

void BFS()
{
	queue<int> q;
	node[1].dis=1;
	q.push(1);
	
	while(!q.empty()&&!ans)
	{
		Edge cur=edge[node[q.front()].head];
		q.pop();
		while(cur.u)
		{
			if(cur.v==1)
			{
				ans=node[cur.u].dis;
				break;
			}
			else if(!node[cur.v].dis)
			{
				q.push(cur.v);
				node[cur.v].dis=node[cur.u].dis+1;
			}
			cur=edge[cur.next];
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>m;
	
	int x,y;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		
		edge[++tot].u=x;
		edge[tot].v=y;
		if(node[x].head)
			edge[tot].next=node[x].head;
		node[x].head=tot;
	}
	
	BFS();
	
	if(ans)
		cout<<ans<<endl;
	else
		cout<<-1<<endl;
	
	return 0;
}
