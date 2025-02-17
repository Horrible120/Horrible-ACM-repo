#include<vector>
#include<cstdio>
#include<iostream>	
using namespace std;
struct DATA
{
	int top;
	vector<int>box;
};
vector<DATA>stack;
int p,dad[30001];
int num[30001];
int a,b,c;
int get_father(int x)
{
	if(x==dad[x]) return x;
	else return dad[x]=get_father(dad[x]);
}
int main()
{
	cin>>p;		
	for(int i=1;i<=30001;i++)
	{
		num[i]=1;
		stack[i].box[++stack[i].top]=i;
	}
	for(int i=1;i<=p;i++)
	{
		cin>>c;
		if(c=='M')
		{
			cin>>a>>b;
			for(int j=1;j<=stack[a].top;j++)
				deep[stack[a].box[j]]+=num[b];	
			int fa=get_father(a),fb=get_father(b);					
			num[fb]+=num[fa],dad[fa]=dad[fb];
		}
		else if(c=='C')
		{
			scanf("%d",&a);
			printf("%d ",deep[a]);
		}
	}
	return 0;
}/***愉***快***的***结***束***了***主***函***数***/
