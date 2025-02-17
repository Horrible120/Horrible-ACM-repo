#include<iostream>
#include<vector>
#include<string>
using namespace std;

const long long M=1e9+7;
int t;
long long l2[100010];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>t;
	
	vector<long long> vn(t+1),vk(t+1);
	
	for(int i=1;i<=t;i++)
		cin>>vn[i];
	for(int i=1;i<=t;i++)
		cin>>vk[i];
	
	l2[0]=1;
	for(int i=1;i<=100000;i++)
		l2[i]=(l2[i-1]*2)%M;
	
	for(int i=1;i<=t;i++)
		cout<<l2[vk[i]]<<endl;
	
	return 0;
}
