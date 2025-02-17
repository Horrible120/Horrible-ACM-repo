#include<map>
#include<queue>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;

struct Node				//字典树节点结构体 
{
	int son[ 27];		//儿子 
	int fail;			//fail指针 
	vector <int> v;
}node[10010];

queue <int> q;			//BFS预处理用队列 

string S[210],T;		//待查单词  待查文章 

int n,tot;			//单词数 
int first[210];			//单词第一次出现的位置 

void insert(string a,int num)				//插入单词到 Trie 中 
{
	int x=0,cur;							//根节点 当前字母(编号) 
	for(int i=0;i<a.size();i++)
	{
		cur=a[i]-'a'; 
		if(!node[x].son[cur]) 
			node[x].son[cur]=++tot; 
		x=node[x].son[cur]; 
	}
	node[x].v.push_back(num); 
}

void AC_pre() 
{
	q.push(0); 
	node[0].fail=0; 
	
	while(!q.empty()) 
	{
		int cur = q.front(); 
		q.pop();
		
		for(int i=0;i<26;i++) 
			if(node[cur].son[i]) 
			{
				int x    = node[cur].son[i]; 
				int Fail = node[cur].fail; 
				
				while(  !node[Fail].son[i] && Fail  ) 
					Fail = node[Fail].fail; 
					
				if( node[Fail].son[i] != x) 
					node[x].fail = node[Fail].son[i];  
				Fail = node[x].fail; 
				
				if( Fail )
					for(int j=0;j<node[Fail].v.size();j++) 
						node[x].v.push_back( node[Fail].v[j] );
				
				q.push( x ); 
			}
	}
}

void AC_search() 
{
	int cur=0,x=0; 
	for(int i=0;i<T.size();i++) 
	{
		x = T[i]-'a'; 
		while( !node[cur].son[x] && cur ) 
			cur = node[cur].fail; 
		cur = node[cur].son[x];
		
		if( node[cur].v.size() ) 
			for(int j=0 ; j< node[cur].v.size() ; j++ ) 
				if( !first[ node[cur].v[j] ] ) 
					first[ node[cur].v[j] ] = i+2-(S[ node[cur].v[j] ].size());
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
	
	AC_search();
	
	for(int i=0;i<=tot;i++)
	{
		printf("Node[ %d ]:    fail: %d\n",i,node[i].fail);
		for(int j=0;j<26;j++)
			if(node[i].son[j])
				printf("    son[ %c ]:  %d\n",j+'a',node[i].son[j]);
		printf("\n");
	}
	
	printf("\n");
	printf("/*****************************************************/\n");
	printf("\n");
	
	for(int i=1;i<=n;i++)
	{
		printf("S[ %d ]:    first  %d    \n",i,first[i]);
	}
	
	return 0;
}
/*

4
he
she
hers
his
ahishers

*/
