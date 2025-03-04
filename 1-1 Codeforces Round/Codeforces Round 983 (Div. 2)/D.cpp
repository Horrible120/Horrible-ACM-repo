#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
using namespace std;

long long tt;

int ask(int a,int b)
{
	cout<<"? "<<a<<' '<<b<<endl;
	int x;
	cin>>x;
	return x;
}

void solve(int n)
{
	vector<int> fa(n+1,-1),son(n+1);
	set<int> mex;
	fa[1]=0;
	for(int i=0;i<n;i++)
		mex.insert(i);
	int cur=n-1;
	mex.erase(n-1);
	while(!(~fa[2]))
	{
		
		int j;
		int m=*mex.rbegin();
		
		if(m==0)
		{
			while(cur)
			{
				fa[cur]=0;
				cur--;
			}
			break;
		}
		
		j=ask(cur,m);
		if(j) mex.erase(m);
		else
		{
			if(m==0)
				fa[cur]=m;
			else
			{
				if(!son[m])
				{
					fa[cur]=m;
					son[m]=cur;
				}
				else
				{
					int so=son[m];
					fa[so]=cur;
					fa[cur]=m;
					son[m]=cur;
				}
			}
			cur--;
			mex.erase(m);
		}
	}
	cout<<"!";
	for(int i=1;i<n;i++)
		cout<<' '<<fa[i];
	cout<<endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		int n;
		cin>>n;
		solve(n);
	}

	return 0;
}


