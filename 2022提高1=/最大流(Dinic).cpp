#include<queue>
#include<cstdio>
#include<iostream>
using namespace std;
/*************************************************************************************/
struct Edge						//链式前向星储存边 
{
	int u,v,f;					//起点 终点 当前剩余流量					
	int next;					//下一条边 
}edge[1000010];

int n,m,s,t;					//点 边 起点 终点 
int first[500010];				//链式前向星 起点数组 
int dis[500010];				//点到起点的距离 
bool book[500010];				//BFS判重用数组 
long long ans;					//最大流量 

queue <int> q;//				//BFS用队列 

void add_edge(int a,int b,int z,int i)	//添加边 起点 终点 权值 编号 
{
	if(first[a])						//如果有边 
		edge[i].next=first[a];			//把他挤到自己后面去 
	first[a]=i;							//自己成为第一个
	edge[i].u=a;						//起点 
	edge[i].v=b;						//终点 
	edge[i].f=z;						//权值 
}

int opp(int x)							//取反向边 ( 1变2 , 2变1 ) 
{
	if(x%2)
		return x+1;
	else
		return x-1;
 } 

bool BFS(int root)						//BFS处理点到起点的距离 
{
		
	for(int i=1;i<=n;++i)				//重置 book & dis 
	{
		book[i]=false;
		dis[i]=0;
	}
	
	q.push(root);						//起点入队 
	book[root]=true;					//标记 
	dis[root]=1;						//默认自己为1 
	
	int x,cur;							//当前扫到的点  当前扫到的边 
	
	while(!q.empty())					//只要不空 
	{
		x=q.front();					//取队首 
		q.pop();						//出队 
		cur=first[x];					//取其连边 
		
		while(cur)						//只要边存在 
		{
			if(!book[edge[cur].v] && edge[cur].f>0)
			{							//没标记过 且 有利用价值 (没有剩余流量就没有意义了) 
				book[edge[cur].v]=true;	//标记 
				q.push(edge[cur].v);	//终点入队 
				dis[edge[cur].v]=dis[x]+1;
			}							//距离 = 父节点距离 + 1 
			cur=edge[cur].next;			//下一条边 
		}	
	}
			
	if(dis[t]>0)						//如果还有路到终点 
		return 1;						//返回 1 
	else								//没有路到终点了的话 
		return 0;						//返回 0 
}

int DFS(int x,int flow)					//DFS实现增广 
{
	if(x==t || flow==0)					//到终点 或 没路了 
		return flow;					//返回当前流量 
		
	int a=0;							//当前边需要支出的流量 
	int cur=first[x];					//取其连边 
	while(cur)							//只要边存在 
	{
		if( dis[edge[cur].v]==dis[x]+1 && edge[cur].f>0 )
										//1--下一节点必须更远离起点,避免回头浪费流量
										//2--这条边可用 
			if(a=DFS( edge[cur].v , min( flow , edge[cur].f ) ))
			{							//继续搜索,如果这条边最终能够成功增广 
				edge[cur].f-=a;			//扣除对应流量 
				edge[opp(cur)].f+=a;	//反向边增加流量 ( 用于反悔 ) 
				return a;				//返回增广容量 
			}		
		cur=edge[cur].next;				//下一条边 
	}
	dis[x]=0;							//到这一步说明这个点的所有出边都不能增广,剪枝 
	return 0;							//返回 0 
}

int main()
{
	int x,y,z;
	
	scanf("%d%d%d%d",&n,&m,&s,&t);
	
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z,2*i-1);			//读入边 
		add_edge(y,x,0,2*i);			//设置反向边 ( 初始流量为0 ) 
	}
	
	while(BFS(s))						//重构图,如果还能增广 
	{
		int a;
		while(a=DFS(s,999999999))		//寻找增广路,找到返回增广容量,否则返回 0  
			ans+=a;						//扩展最大容量 
	}
	
	printf("%lld\n",ans);				//输出答案 
	
	return 0;
}
