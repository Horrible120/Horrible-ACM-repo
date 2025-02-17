#include<iostream>
using namespace std;

int t;

int ask(int x,int y)
{
	int res=0;
	cout<<"? "<<x<<' '<<y<<endl;
	cin>>res;
	return res;
}

void ans(int x)
{
	cout<<"! "<<x<<endl;
	return;
}

void solve(int n)
{
	if(n==3)
	{
		if(ask(n,n-1)==ask(n-1,n))
			ans(n-2);
		else if(ask(n,n-2)==ask(n-2,n))
			ans(n-1);
		else
			ans(n);
			
		return;
	}
	if(n==4)
	{
		int cd1=(ask(n,n-1)==ask(n-1,n)),cd2=(ask(n,n-2)==ask(n-2,n));
		if(cd1&&cd2)
			ans(n-3);
		else if(!cd1&&cd2)
			ans(n-1);
		else if(cd1&&!cd2)
			ans(n-2);
		else
			ans(n);
		return;
	}
	if(n==5)
	{
		int a=ask(n,n-1),b=ask(n-1,n-2),c=ask(n-2,n);
		if(a^b^c)
			if(ask(n,n-3)==ask(n-3,n))
				ans(n-4);
			else
				ans(n-3);
		else
			if(ask(n-1,n)==a)
				ans(n-2);
			else
				if(ask(n,n-2)==c)
					ans(n-1);
				else
					ans(n);
		return;
	}
	if(ask(n,n-1)==ask(n-1,n)) 
		solve(n-2);
	else if(ask(n,n-2)==ask(n-2,n))
		ans(n-1);
	else
		ans(n);
	return;
}

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
		solve(n);
	}
	
	return 0;
}
