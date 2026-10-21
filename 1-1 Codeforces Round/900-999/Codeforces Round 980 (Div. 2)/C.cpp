#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<vector>
#include<random>
#include<algorithm>
using namespace std;

struct Pair
{
	int u,v;
};

int t;

bool cmp(Pair a,Pair b)
{
	if(a.u+a.v!=b.u+b.v)return a.u+a.v<b.u+b.v;
	return a.u<b.u;
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
		vector<Pair> v(n);
		for(int i=0;i<n;i++)
			cin>>v[i].u>>v[i].v;
		sort(v.begin(),v.end(),cmp);
		for(int i=0;i<n;i++) cout<<v[i].u<<' '<<v[i].v<<' ';
		cout<<endl;
	}
	
	return 0;
}
