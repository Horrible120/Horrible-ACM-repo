#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

struct Node
{
	int sum;
	int son[27];
	bool end;
}node[100010];

int n,m;
int tot,op;

char S[1010];

void insert(char word[])
{
	int cur=0;
	int l=strlen(word);
	
	for(int i=0;i<l;i++)
	{
		if(!node[cur].son[word[i]-'a'+1])
			node[cur].son[word[i]-'a'+1]=++tot;
		cur=node[cur].son[word[i]-'a'+1];
		node[cur].sum++;
	}
	node[cur].end=1;
}

bool find(char word[])
{
	int cur=0;
	int l=strlen(word);
	
	for(int i=0;i<l;i++)
		if(!node[cur].son[word[i]-'a'+1])
			return 0;
		else
			cur=node[cur].son[word[i]-'a'+1];
			
	return node[cur].end;
}

int get_sum(char word[])
{
	int cur=0;
	int l=strlen(word);
	
	for(int i=0;i<l;i++)
		if(!node[cur].son[word[i]-'a'+1])
			return 0;
		else
			cur=node[cur].son[word[i]-'a'+1];
			
	return node[cur].sum;
}

int main()
{
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=n;i++)
	{
		gets(S);
		insert(S);
	}
	
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==0)
		{
			gets(S);
			printf("%d",find(S));
		}
		if(op==1)
		{
			gets(S);
			printf("%d",get_sum(S));
		}
	}
		
	
	return 0;
}
