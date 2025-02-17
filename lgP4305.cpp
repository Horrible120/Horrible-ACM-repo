#include<iostream>
#include<vector>
#include<map>
using namespace std;

int t;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	int n;
	while(t--)
	{
		cin>>n;
		int x;
		vector<int> v;
		map<int,int> vs;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			if(!vs[x])
			{
				v.push_back(x);
				vs[x]=1;
			}
		}
		for(int i=0;i<v.size();i++)
			cout<<v[i]<<' ';
		cout<<endl;
			
		
	}
	
	return 0;
 } 
