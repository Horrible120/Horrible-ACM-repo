#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm> 
using namespace std;

/********************************************************************************/

int p[100001],len,ans;
string s1,s2;

/********************************************************************************/

void KMP(string s)
{
	for(int i=1;i<s.size();i++)
	{
		len=p[i-1];
		while(1)
		{
			if(s[i]==s[len])
			{
				p[i]=len+1;
				break;
			}
			if(len==0)
				break;
			len=p[len-1];
		} 
	}
}

/********************************************************************************/

int main()
{
	cin>>s1>>c2;
	KMP(s2);
	len=0;
	for(int i=0;i<s1.size();i++)
	{
		if(s[i]==s[len])
		{
			len++;
			if(len==s2.size())
				break;
		} 
		else
	}
	return 0;
}
