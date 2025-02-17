#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

int t;

bool cmp(int a,int b)
{
	return a>b;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	 
	int n;
	string s;
	while(t--)
	{
		cin>>n;
		cin>>s;
		int flag=1;
		if(s[0]=='1'||s[n-1]=='1')
		{
			cout<<"YES"<<endl;
			continue;
		}
		for(int i=1;i<n-2&&flag;i++)
			if(s[i]=='1'&&s[i+1]=='1')
			{
				cout<<"YES"<<endl;
				flag=0;
			}		
		if(flag)	
			cout<<"NO"<<endl;
	}
	
	return 0;
}
