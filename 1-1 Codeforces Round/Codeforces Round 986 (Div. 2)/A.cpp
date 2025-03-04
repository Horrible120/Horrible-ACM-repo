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

mt19937_64 rnd(time(0));

typedef long long ll;
typedef uint64_t ull;


const ll INF=1e18,
		 Mod=1e9+7;

ll tt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> tt;

	while (tt--) {
		ll n,a,b;
		cin>>n>>a>>b;
		string s;
		cin>>s;
		ll x=0,y=0,flag=0;
		for(int i=1;i<=20;i++)
			for(int j=0;j<n;j++){
				if(s[j]=='N')
					y++;
				if(s[j]=='E')
					x++;
				if(s[j]=='S')
					y--;
				if(s[j]=='W')
					x--;
				if(x==a&&y==b)
					flag=1;
			}
		if(flag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}

	return 0;
}

