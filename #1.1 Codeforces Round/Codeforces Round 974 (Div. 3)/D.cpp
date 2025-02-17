#include<iostream>
#include<vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int t=0;
	
	cin>>t;
	
	while(t--)
	{
		int n,d,k;
		cin>>n>>d>>k;
		
		vector<int> st(n+2),ed(n+2),sover(n+2),tover(n+2);
		int l,r;
		
		for(int i=1;i<=k;i++)
		{
			cin>>l>>r;
			st[l]++;
			ed[r]++;
		}
		
		
		sover[1]=ed[1];
		tover[n]=st[n];
		for(int i=2;i<=n;i++)
			sover[i]=sover[i-1]+ed[i];
		for(int i=n-1;i>=1;i--)
			tover[i]=tover[i+1]+st[i];
		
		int mx=0,mn=1000000;
		int ansx,ansn;
		
		/*for(int i=1;i<=n;i++)
			cout<<sover[i]<<' ';
		cout<<endl;
		for(int i=1;i<=n;i++)
			cout<<tover[i]<<' ';
		cout.flush();*/
		
		for(int i=1;i<=n-d+1;i++)
		{
			if(k-(sover[i-1]+tover[i+d])>mx)
			{
				mx=k-(sover[i-1]+tover[i+d]);
				ansx=i;
			}
			if(k-(sover[i-1]+tover[i+d])<mn)
			{
				mn=k-(sover[i-1]+tover[i+d]);
				ansn=i;
			}
		}
		cout<<ansx<<' '<<ansn<<endl;
	}
	
	return 0;
}
