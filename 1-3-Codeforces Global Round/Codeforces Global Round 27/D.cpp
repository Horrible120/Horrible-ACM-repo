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

mt19937_64 rnd( time( 0 ) );

typedef long long ll;
typedef uint64_t ull;


const ll INF = 1e18,
         Mod = 1e9+7;

ll tt;

ll c[60];

void init() {
	c[0] = 2;

	for (ll i = 1; i <= 50; i++)
		c[i] = c[i - 1] * c[i - 1] % Mod;
}

ll Pow(ll k) {
	ll cnt = 0, ret = 1;

	while (k) {
		if (k & 1) ret = ret * c[cnt] % Mod;

		cnt++;
		k >>= 1;
	}

	return ret;
}

struct cmp {
	operator()(pair<ll, ll> a, pair<ll, ll> b) {
		return a.first < b.first;
	}
};

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );


	init();
	cin >> tt;

	while ( tt-- ) {
		ll n;
		cin >> n;
		vector<ll> v(n + 1),s(n+1), t(n+1), p(n + 1);

		for (ll i = 1; i <= n; i++)
			cin >> v[i];

		ll cnt = 0, sum = 0;

		ll  top = 0;


		for (ll i = 1; i <= n; i++) {
			cnt = 0;
			sum = (sum+v[i])%Mod;
			while (!(v[i] % 2)) {
				cnt++;
				v[i] >>= 1;
			}

			

			s[++top] = v[i];
			t[top] = cnt;

			while (top > 1 && log2l(s[top]) + t[top] > log2l(s[top - 1])) {
				
				sum=(sum+
					(s[top]*((Pow(t[top]+t[top-1])-Pow(t[top])+Mod)%Mod))-
					(s[top-1]*(Pow(t[top-1])-1))%Mod+Mod)%Mod;
				
				t[top-1]+=t[top];
				s[top-1]=s[top];
				s[top]=0;
				t[top]=0;
				top--;
			}
			
			cout<<sum<<' ';
		}

		cout << endl;
	}

	return 0;
}
