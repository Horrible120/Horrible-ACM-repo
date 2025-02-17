#include<iostream>
#include<string>
#include<vector>
using namespace std;

int t;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	while(t--)
	{
		int n;
		string a={},b={};
		cin>>n;
		cin>>a>>b;
		
		bool flag=1;
		for(int i=1;i<a.length();i++)
			if((a[i]==b[i])^(a[i-1]==b[i-1]))
			{
				flag=0;
				break;
			}
		if(!flag)
			cout<<"NO"<<endl;
		else
		{
			vector<int> l,r;
			cout<<"YES"<<endl;
			for(int i=0;i<n-1;i++)
				if(a[i]!=a[i+1])
				{
					l.push_back(1);
					r.push_back(i+1);
				}
			if(a[n-1]=='1'&&b[0]=='0')
			{
				l.push_back(1);
				r.push_back(n);
			}
			if(b[0]=='1'&&a[n-1]=='1')
			{
				l.push_back(1);
				r.push_back(1);
				l.push_back(2);
				r.push_back(n);
			}
			if(a[n-1]=='0'&&b[0]=='1')
			{
				l.push_back(1);
				r.push_back(n);
				l.push_back(1);
				r.push_back(1);
				l.push_back(2);
				r.push_back(n);
			}
			cout<<l.size()<<endl;
			for(int i=0;i<l.size();i++)
				cout<<l[i]<<' '<<r[i]<<endl;
		}
		
	}
	
	return 0;
}
