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
	
	int n;
	while(t--)
	{
		string a={},b={};
		cin>>n;
		vector<int> dpa(n+1),dpb(n+1);
		cin>>a>>b;
		
		for(int i=0;i<n;i++)
		{
			if(a[i]=='J') a[i]=0;
			else a[i]=1;
			if(b[i]=='J') b[i]=0;
			else b[i]=1;
		}
			
		if(a[0]+b[0]+a[1]>=2) dpa[2]=1;
		if(a[0]+b[0]+b[1]>=2) dpb[2]=1;
		for(int i=3;i<=n;i++)
		{
			if(i%3==0)
			{	
				dpa[i]=dpb[i-3];
				if(a[i-1]+a[i-2]+a[i-3]>=2)
					dpa[i]++;	
				
				dpb[i]=max(max(dpa[i],dpa[i-1]),dpb[i-1]);		
				if(b[i-1]+b[i-2]+b[i-3]>=2)
					dpb[i]=max(dpb[i],dpa[i]+1);
				if(b[i-1]+b[i-2]+a[i-1]>=2)
					dpb[i]=max(dpb[i],dpa[i-1]+1);
				if(b[i-1]+a[i-2]+a[i-1]>=2)
					dpb[i]=max(dpb[i],dpb[i-1]+1);
			}
			if(i%3==1)
			{
				dpa[i]=dpb[i-2];
				if(a[i-1]+a[i-2]+a[i-3]>=2)
					dpa[i]++;
					
				dpb[i]=dpa[i-2];
				if(b[i-1]+b[i-2]+b[i-3]>=2)
					dpb[i]++;	
			}
			if(i%3==2)
			{
				dpa[i]=max(dpb[i-1],dpb[i-2]);
				if(a[i-1]+a[i-2]+a[i-3]>=2)
					dpa[i]=max(dpa[i],dpb[i-1]+1);
				if(a[i-1]+a[i-2]+b[i-2]>=2)
					dpa[i]=max(dpa[i],dpb[i-2]+1);
				
				dpb[i]=max(dpa[i-1],dpb[i-2]);
				if(b[i-1]+b[i-2]+b[i-3]>=2)
					dpb[i]=max(dpb[i],dpa[i-1]+1);
				if(b[i-1]+a[i-2]+b[i-2]>=2)
					dpb[i]=max(dpb[i],dpb[i-2]+1);	
			}
		}
		cout<<dpb[n]<<endl;
	}
	
	return 0;
}
