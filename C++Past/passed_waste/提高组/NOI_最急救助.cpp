#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
int n,q[110],qmax;
string name[110];
string sos;
int main()
{
	scanf("%d",&n); 
	for(int i=1;i<=n;i++)
		
	for(int i=1;i<=n;i++)
	{
		cin>>name[i]>>sos;
		for(int j=0;j<sos.length();j++)
			if(sos[j]=='s'&&sos[j+1]=='o'&&sos[j+2]=='s')
				q[i]++;	
		qmax=max(qmax,q[i]);			
	}
		
	for(int i=1;i<=n;i++)
		if(q[i]==qmax)
			cout<<name[i]<<endl;		
	printf("%d",qmax);
	return 0;
}
