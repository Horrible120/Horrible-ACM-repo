#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n,ans;

bool cmp(int a,int b)
{
	return a>b;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n;
	
	vector<int> v(n),b(n);
	
	for(int i=0;i<n;i++)
		cin>>v[i];
	for(int i=0;i<n-1;i++)
		cin>>b[i];
		
	sort(v.begin(),v.end(),cmp);
	sort(b.begin(),b.end(),cmp);
	
	int flag=0,coo=0;
	
	for(int i=0;i<n&&flag<2;i++)
		if(v[i]>b[i-flag])
			if(flag==0)
				ans=v[i],flag++;
			else
				flag++;
				
	if(flag==2)
		cout<<-1<<endl;
	if(flag==1)
		cout<<ans<<endl;
	if(flag==0)
		cout<<v[n-1]<<endl;
	return 0;
}
