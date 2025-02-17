#include<string>
#include<iostream>
using namespace std;

string biga,bigb;
int ans[5000]={};

void turn(string &a)
{
	string x=a;
	for(int i=0;i<a.length();i++)
		a[i]=x[a.length()-1-i];
	return;
}

void Add(string aa,string bb)
{
	if(aa<bb) swap(aa,bb);
	
	turn(aa);
	turn(bb);
	
	int a[5000]={},b[5000]={};
	
	for(int i=1;i<=aa.length();i++)
		a[i]=aa[i-1]-'0';
	for(int i=1;i<=bb.length();i++)
		b[i]=bb[i-1]-'0';	
	
	for(int i=1;i<=aa.length();i++)
	{
		ans[i]+=a[i]+b[i];
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}	
	
	int n=aa.length();
	
	if(ans[n+1]!=0) n++;
	
	for(int i=n;i>=1;i--)
		cout<<ans[i];
	
	return;	
}

void Sub(string aa,string bb)
{
	bool sig=true;
	if(aa<bb)
	{
		swap(aa,bb);
		sig=false;
	}
	
	turn(aa);
	turn(bb);
	
	int a[5000]={},b[5000]={};
	
	for(int i=1;i<=aa.length();i++)
		a[i]=aa[i-1]-'0';
	for(int i=1;i<=bb.length();i++)
		b[i]=bb[i-1]-'0';	
	
	for(int i=1;i<=aa.length();i++)
	{
		ans[i]+=a[i]-b[i];
		if(ans[i]<0)
		{
			a[i+1]--;
			ans[i]%=10;
		}
	}
	
	if(!sig) cout<<'-';
	
	int n=aa.length();
	while((!ans[n])&&n>1) n--;
	for(int i=n;i>=1;i--)
		cout<<ans[i];
	
	return;
}

void Mul(string aa,string bb)
{
	turn(aa);
	turn(bb);
	
	int a[5000]={},b[5000]={};
	
	for(int i=1;i<=aa.length();i++)
		a[i]=aa[i-1]-'0';
	for(int i=1;i<=bb.length();i++)
		b[i]=bb[i-1]-'0';	
		
	for(int i=1;i<=aa.length();i++)
		for(int j=1;j<=bb.length();j++)
			ans[i+j-1]+=a[i]*b[j];
	for(int i=1;i<=aa.length()+bb.length();i++)
	{
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	
	int n=aa.length()+bb.length();
	
	while((!ans[n])&&n>1) n--;
	
	for(int i=n;i>=1;i--)
		cout<<ans[i];
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin>>biga>>bigb;
	
	Mul(biga,bigb);
	
	return 0;
} 
