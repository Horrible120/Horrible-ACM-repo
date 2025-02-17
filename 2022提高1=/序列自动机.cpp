#include<queue>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;

int nxt[200010][27];
int fa[200010];
int len;

bool book[200010];

char T[200010];

queue <int> q;

void DFS(int x)
{
	if(x<0)
		return;
	else
	{
		DFS(fa[x]);
		putchar(T[x]);
	}
}

int main()
{
	gets(T);
	
	len=strlen(T);
	
	
	for(int i=0;i<26;i++)
		nxt[len][i]=-1;
	
	for(int i=len-1;i>=0;i--)
	{
		for(int j=0;j<26;j++)
			nxt[i][j]=nxt[i+1][j];
		nxt[i][T[i]-'a']=i;
		fa[i]=-2;
	}
	
	q.push(-1);
	
	int cur;
	
	while(!q.empty())
	{
		cur=q.front();
		q.pop();
		
		for(int i=0;i<26;i++)
		{
			if(nxt[cur+1][i]==-1)
			{
				DFS(cur);
				putchar(i+'a');
				return 0;
			}
			else if(fa[nxt[cur+1][i]]==-2)
			{
				fa[nxt[cur+1][i]]=cur;
				q.push(nxt[cur+1][i]);
			}
		}
	}
	
	return 0;
}
