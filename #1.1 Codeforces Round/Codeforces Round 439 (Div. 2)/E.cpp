#include<iostream>
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<cstdint>
#include<vector>
#include<random>
#include<string>
#include<algorithm>
using namespace std;

mt19937_64 rnd(time(0));

int n,m,q;
map<vector<int>,uint64_t> mp;

int LB(int x)
{
	return x&-x;
}

void xr(vector<vector<vector<uint64_t>>> &tr,int r1,int c1,uint64_t x)
{
	if(r1>=1&&r1<=n&&c1>=1&&c1<=m)
	{
		for(int i=r1;i<=n;i+=LB(i))
		{
			for(int j=c1;j<=m;j+=LB(j))
			{
				tr[0][i][j]^=x;
				tr[1][i][j]^=x*(i&1);
				tr[2][i][j]^=x*(j&1);
				tr[3][i][j]^=x*(i&j&1);
			}
		}	
	} 
}

void range_xr(vector<vector<vector<uint64_t>>> &tr,int r1,int c1,int r2,int c2,uint64_t x)
{
	xr(tr,r1,c1,x);
	xr(tr,r1,c2+1,x);
	xr(tr,r2+1,c1,x);
	xr(tr,r2+1,c2+1,x);
	 
}

uint64_t ask(vector<vector<vector<uint64_t>>> &tr,int r1,int c1)
{
	uint64_t res=0;
	for(int i=r1;i;i-=LB(i))
	{
		for(int j=c1;j;j-=LB(j))
		{
			res^=tr[0][i][j];
			res^=tr[1][i][j]*((~n)&1);
			res^=tr[2][i][j]*((~m)&1);
			res^=tr[3][i][j]*((~n)&(~m)&1);
		}
	}
	return res;
}

uint64_t range_ask(vector<vector<vector<uint64_t>>> &tr,int r1,int c1,int r2,int c2)
{
	uint64_t res=0;
	res^=ask(tr,r1-1,c1-1);
	res^=ask(tr,r2,c1-1);
	res^=ask(tr,r1-1,c2);
	res^=ask(tr,r2,c2);
	return res;
}

uint64_t get_ans(vector<vector<vector<uint64_t>>> &tr,int r1,int c1,int r2,int c2)
{
	uint64_t res=0;
	for(int i=r1;i;i-=LB(i))
		for(int j=c1;j;j-=LB(j))
			res^=tr[0][i][j];
	for(int i=r2;i;i-=LB(i))
		for(int j=c2;j;j-=LB(j))
			res^=tr[0][i][j];
	return res;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
		
	cin>>n>>m>>q;
	
	vector<vector<vector<uint64_t>>> tr(4,vector<vector<uint64_t>>(n+1,vector<uint64_t>(m+1)));
	
	int op,r1,r2,c1,c2;
	for(int i=1;i<=q;i++)
	{
		cin>>op>>r1>>c1>>r2>>c2;
		if(op==1||op==2)
		{
			if(op==1)
				mp[{r1,c1,r2,c2}]=rnd();
			range_xr(tr,r1,c1,r2,c2,mp[{r1,c1,r2,c2}]);
		}	
		else
			cout<<(get_ans(tr,r1,c1,r2,c2)?"No":"Yes")<<endl;
	}

	return 0;
}

