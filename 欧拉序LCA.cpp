#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int N,M,S,tot;
bool vis[500010];

struct Node//链式前向星 
{
	int head;
	int map;
};

struct Edge
{
	int u,v,next;
};

struct Dfn//DFS序结构体，num是节点编号，dpt是节点深度 
{
	int num,dpt;
	Dfn(int a,int b){num=a,dpt=b;}
};

vector<vector<Dfn>> DFSX;//DFS序ST表 
vector<Node> node(500010);
vector<Edge> edge(1000010);

void DFS(int x,int dp)//当前节点与深度 
{
	vis[x]=1;
	DFSX.push_back({Dfn(x,dp)});
	node[x].map=DFSX.size()-1;//记录节点第一次在DFS序中的位置 
	
	
	Edge cur=edge[node[x].head];
	while(cur.v)
	{
		
		if(!vis[cur.v])
		{
			DFS(cur.v,dp+1);
			DFSX.push_back({Dfn(x,dp)});//生成DFS序 
		}
			
		cur=edge[cur.next];
	}
	return ;
	
}

void ST()//ST表预处理 
{
	for(int i=1;i<=30;i++)
		for(int j=0;j<DFSX.size();j++)
			if(j+(1<<(i-1))<DFSX.size())
				if(DFSX[j][i-1].dpt<DFSX[j+(1<<(i-1))][i-1].dpt)
					DFSX[j].push_back(DFSX[j][i-1]);
				else
					DFSX[j].push_back(DFSX[j+(1<<(i-1))][i-1]);
			else
				DFSX[j].push_back(DFSX[j][i-1]);
	//cout<<"DDDD"<<endl;
}

Dfn solve(int x,int y)//回答查询 
{
	if(node[x].map>node[y].map)
		swap(x,y);
	
	int t=log2(node[y].map-node[x].map);//[x,y]中的元素个数 
	
	if (DFSX[node[x].map][t].dpt<DFSX[node[y].map-(1<<t)+1][t].dpt)//ST表获取区间最值 
		return DFSX[node[x].map][t];
	return DFSX[node[y].map-(1<<t)+1][t];
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>N>>M>>S;
	
	int u,v;
	for(int i=1;i<N;i++)
	{
		cin>>u>>v;
		
		edge[2*i-1].next=node[u].head;
		edge[2*i-1].u=u;
		edge[2*i-1].v=v;
		node[u].head=2*i-1;
		
		edge[2*i].next=node[v].head;
		edge[2*i].u=v;
		edge[2*i].v=u;
		node[v].head=2*i;
	}
	
	DFS(S,1);//跑DFS 
	ST();//预处理ST表 
	
	int x,y;
	for(int i=1;i<=M;i++)
	{
		cin>>x>>y;
		cout<<((x==y)?x:solve(x,y).num)<<endl;
	}
	
	return 0;
}
