#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<cmath>
using namespace std;

int t;

int main()
{
	cin>>t;
	
	while(t--)
	{
		int n,m,q,flag;
		cin>>n>>m>>q;
		
		vector<int> v(n+5);
		vector<int> vis(n+5);
		vector<int> mv(m+5);
		
		for(int i=1;i<=n;i++)
			cin>>v[i];
		for(int i=1;i<=m;i++)
			cin>>mv[i];
		
		int cur=1;
		flag=1;	
		for(int i=1;i<=m;i++)
		{
			if((mv[i]!=v[cur])&&(!vis[mv[i]]))
			{
				flag=0;
				//cout<<"WWW"<<i<<' '<<cur<<' '<<vis[v[cur]]<<endl;
				break;
			}
			vis[mv[i]]=1;
			if(cur<=n&&mv[i]==v[cur]) cur++;
		}
		if(flag)
		{
			cout<<"YA"<<endl;
		}
		else 
			cout<<"TIDAK"<<endl;
	}
	
	return 0;
} 
