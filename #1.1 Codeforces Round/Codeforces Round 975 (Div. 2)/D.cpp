#include<iostream>
#include<vector>
#include<algorithm>
using namespace std; 

int t;

struct Cd
{
	int coo;
	int a;
	Cd(){}; 
};

bool cmp(Cd u,Cd v)
{
	return u.a<v.a;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	while(t--)
	{
		int n;
		cin>>n;
		vector<Cd> v(n);
		
		for(int i=0;i<n;i++)
			cin>>v[i].a;
		for(int i=0;i<n;i++)
			v[i].coo=i;
			
		sort(v.begin(),v.end(),cmp);
		
		int maxl=0,minr=n-1,minl=n-1,maxr=0,cur=0,flag=1;
		for(int i=v[0].a;i<n;i++)
		{
			while(v[cur].a<=i&&cur<=n) 
			{
				minl=min(minl,v[cur].coo);
				maxr=max(maxr,v[cur].coo);
				cur++;
			}//cout<<"qs"<<i<<':'<<minl<<' '<<maxr<<endl;
				if(maxr-minl+1>i) flag=0;
				maxl=max(maxl,maxr-i+1);
				minr=min(minr,minl+i-1);
		}
		if(!flag)
		{
			cout<<0<<endl;
			continue;
		}
		cout<<minr-maxl+1<<endl;
	}
	
	return 0;
}
