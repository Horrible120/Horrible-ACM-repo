#include<map>
#include<queue>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;

struct Node
{
	int son[ 27];
	int fail;
	vector <int> ex;
}node[10010];

queue <int> q;

string S[210],T;

int n,tot;
int first[210];

bool vis[210];

void insert(string a,int num)
{
	int x,cur;
	for(int i=0;i<a.size();i++)
	{
		cur=a[i]-'a';
		if(!node[x].son[cur])
			node[x].son[cur]=++tot;
		x=node[x].son[cur];
	}
	node[x].ex.push_back(num);
	node[]
}

void AC_pre()
{
	q.push(0);
	node[0].fail=0;
	
	int cur,Fail;
	
	while(!q.empty())
	{
		cur=q.front();
		q.pop();
		
		for(int i=0;i<26;i++)
			if(node[cur].son[i])
			{
				int Son=node[cur].son[i];
				for(int j=0;j<node[cur].ex.size();j++)
					node[Son].ex.push_back( node[cur].ex[j] );
				
				Fail=cur;
				while(Fail && (!node[Son].fail))
				{
					Fail=node[Fail].fail;
					if(node[Fail].son[i])
						node[Son].fail=node[Fail].son[i];
				}
				
				q.push(node[cur].son[i]);
			}
	}
	
}

void AC_search()
{
	int cur,x=0;
	for(int i=0;i<T.size();i++)
	{
		cur=T[i]-'a';
		
		while(!node[x].son[cur] && x)
			x=node[x].fail;
		if(node[x].son[cur])
			for(int j=0;j<node[x].ex.size();j++)
				if(!vis[node[x].ex[j]])
					first[node[x].ex[j]]=
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>S[i];
		insert(S[i],i);
	}
	cin>>T;
	
	AC_pre();
	
	for(int i=0;i<=tot;i++)
	{
		printf("Node[ %d ]:    fail: %d\n",i,node[i].fail);
		for(int j=0;j<26;j++)
			if(node[i].son[j])
				printf("    son[ %c ]:  %d\n",j+'a',node[i].son[j]);
		printf("\n");
	}
	
	return 0;
}
/*

4
she
he
hers
his
ahishers

*/
