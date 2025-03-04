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

typedef long long ll;
typedef uint64_t ull;

ll tt;

string s;

ll check(ll x)
{
	ll d=0,g=0,l=s.size()-3;
	for(int i=max(0*1ll,x-3);i<min(x+1,l);i++)
		if(s[i]=='1'&&s[i+1]=='1'&&
			s[i+2]=='0'&&s[i+3]=='0')
				d++;
	if(s[x]=='0')
		s[x]='1';
	else
		s[x]='0';
	for(int i=max(0*1ll,x-3);i<min(x+1,l);i++)
		if(s[i]=='1'&&s[i+1]=='1'&&
			s[i+2]=='0'&&s[i+3]=='0')
				g++;	
	return g-d;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin>>tt;

	while(tt--)
	{
		s={};
		
		cin>>s;
		ll q;
		cin>>q;
		ll cnt=0;
		
		for(int i=0;i<s.size()-3;i++)
			if(s[i]=='1'&&s[i+1]=='1'&&
				s[i+2]=='0'&&s[i+3]=='0')
					cnt++;
		ll x,y;
		
		//cout<<">>>"<<cnt<<endl;
		for(int i=1;i<=q;i++)
		{
			cin>>x>>y;
			if(y!=s[x-1]-'0')
			{
				cnt+=check(x-1);
				
			}
				
			
			//cout<<">>>"<<cnt<<' '<<s[x-1]<<endl<<"<<<";
				
			if(cnt)
				cout<<"YES"<<endl;
			else
				cout<<"NO"<<endl;
		}
		
		
		
	}

	return 0;
}


