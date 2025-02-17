#include<vector>
#include<cstdio>
#include<iostream>
using namespace std;

struct Node
{
	int dad;
	int dp[601];
	int num;
	vector <int> v;
}node[3010];

int n,m;

int DFS(int a)
{
	for(int i=0;i<node[a].v.size();i++)
	{
		DFS(node[a].v[i]);
		for(int j=m+1;j>=2;j--)
			for(int k=1;k<j;k++)
				node[a].dp[j]=max(  node[a].dp[j]  ,  node[a].dp[k]+node[node[a].v[i]].dp[j-k]  );
	}
	for(int i=1;i<=m+1;i++)
		node[a].dp[i]+=node[a].num;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&node[i].dad,&node[i].num);
		node[node[i].dad].v.push_back(i);
	}
	DFS(0);
	printf("%d",node[0].dp[m+1]);
	return 0;
}
/*

7 4
2 2
0 1
0 4
2 1
7 1
7 6
2 2

*/
