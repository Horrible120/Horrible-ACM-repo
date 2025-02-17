#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

int t,n;

bool ask(string s)
{
	bool res=0;
	cout<<"? "<<s<<endl;
	cin>>res;
	return res;
}

void answer(string s)
{
	cout<<"! "<<s<<endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	int cnt=1;
	int flag=1;
	
	for(int i=1;i<=t;i++)
	{
		cin>>n;
		
		string ans="";
		
		while(ans.length()<n)
		{
			if(ask(ans+"0"))
			{
				ans=ans+"0";
				continue;
			}
			if(ask(ans+"1"))
			{
				ans=ans+"1";
				continue;
			}
			break;
		}
		while(ans.length()<n)
		{
			if(ask("0"+ans))
			{
				ans="0"+ans;
				continue;
			}
			else
			{
				ans="1"+ans;
				continue;
			}
		}
		answer(ans);
		cout.flush();
	}
	
	return 0;
}
