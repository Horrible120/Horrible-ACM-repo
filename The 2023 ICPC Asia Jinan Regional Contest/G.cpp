#include<iostream>
#include<vector>
#include<string>
using namespace std;

int T,ans;
const int M=1e9+7;
int p[1000001];

int get_fa(vector<int> &dsu,int x)
{
	
	if(x==dsu[x]) return x;
	return dsu[x]=get_fa(dsu,dsu[x]);
}

void merge(vector<int> &dsu,int x,int y)
{
	if(get_fa(dsu,x)==get_fa(dsu,y))
		return;
	else
	{
		ans--;
		//cout<<"ANS--!!!"<<x<<':'<<get_fa(dsu,x)<<'|'<<y<<':'<<get_fa(dsu,y)<<endl;
		dsu[get_fa(dsu,y)]=get_fa(dsu,x);
		return;
	}
}

void solve(int &r,int &c,vector<vector<bool>> &v)
{
	int flag=0;//ÊÇ·ñÎÞ½â 
	vector<int> dsu(2*r+1);
	ans=2*r;
	
	for(int i=1;i<=2*r;i++)
		dsu[i]=i;
	
	for(int i=1;i<=(c+1)/2;i++)
	{
		
		int sum=0,l1=0,l2=0,r1=0,r2=0;
		for(int j=1;j<=r;j++)
		{
			sum+=v[j][i];
			sum+=v[j][c+1-i];
			
			if(v[j][i])
				if(l1==0) l1=j;
				else l2=j; 
			if(v[j][c+1-i])
				if(r1==0) r1=j;
				else r2=j; 
			
			
		}
		if(c%2==1&&i==(c+1)/2)
		{
			if(sum>2) flag=1;	
		}
		else
		{
			if(sum>2)
				flag=1;
			else if(r1&&l1)
				merge(dsu,r1,l1),merge(dsu,l1+r,r1+r);
			else if(r1&&r2)
				merge(dsu,r1,r2+r),merge(dsu,r2,r1+r);
			else if(l1&&l2)
				merge(dsu,l1,l2+r),merge(dsu,l2,l1+r);
			//cout<<sum<<"!!!"<<l1<<' '<<l2<<' '<<r1<<' '<<r2<<endl;
		}
			
			
	}
	
	for(int i=1;i<=r;i++)
		if(get_fa(dsu,i)==get_fa(dsu,i+r))
			flag=1;
	
	//cout<<flag<<" ANS ";	
	if(flag) cout<<0<<endl;
	else cout<<p[ans/2]<<endl;
	
	return;
} 

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	p[0]=1;
	for(int i=1;i<=1e6;i++)
		p[i]=p[i-1]*2%M;
	
	//for(int i=1;i<=30;i++)
	//	cout<<p[i]<<endl;
	
	cin>>T;
	
	while(T--)
	{
		int r,c;
		cin>>r>>c;
		vector<vector<bool>> v(r+1,vector<bool>(c+1));
		
		string s;
		
		for(int i=1;i<=r;i++)
		{
			cin>>s;
			for(int j=0;j<c;j++)
			{
				v[i][j+1]=(s[j]=='1');
				//cout<<v[i][j+1]<<endl;
			}
		}
			
		solve(r,c,v);	
				
		
	}
	
	return 0;
 } 
