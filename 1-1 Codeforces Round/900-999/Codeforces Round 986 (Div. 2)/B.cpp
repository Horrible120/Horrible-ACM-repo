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
		ll n,b,c,ans;
		cin>>n>>b>>c;
		
		if(b==0){
			if(c<=n-3)
				cout<<-1<<endl;
			else if(c<=n-1)
				cout<<n-1<<endl;
			else
				cout<<n<<endl;
			continue;
		}
		
		ans=n;
		if(n-1>=c)
			ans-=(n-1-c)/b+1;
		cout<<ans<<endl;
	}

	return 0;
}

