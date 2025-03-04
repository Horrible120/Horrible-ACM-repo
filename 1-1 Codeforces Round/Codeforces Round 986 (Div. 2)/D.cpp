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

struct cmp {
	bool operator()( const pair<ll, ll> &a, const pair<ll, ll> &b ) const {
		return a.first < b.first;
	}
};


int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );

	cin >> tt;

	while ( tt-- ) {
		ll n;
		cin >> n;
		vector<vector<pair<ll, ll>>> p( 3, vector<pair<ll, ll>>( n + 1 ) );	//储存 Q K J 的策略

		set<pair<ll, ll>, cmp> s[3];	//以重要程度为关键字排序

		vector<pair<ll, ll>> ans;	//储存答案 fir是交易对象 sec是交易牌型

		vector<ll> book( n + 1 );
		vector<pair<ll, ll>> last( n + 1 );

		ll x;

		for ( int i = 0; i < 3; i++ ) {
			for ( int j = 1; j <= n; j++ ) {
				cin >> x;
				p[i][j].first = x;
				p[i][j].second = j;
				s[i].insert( make_pair( x, j ) );
			}
		}

		book[1] = true;

		for ( int i = 1; i <= n; i++ ) {
			if ( book[i] )
				for ( int j = 0; j < 3; j++ ) {
					while ( ( *s[j].begin() ).first < p[j][i].first ) {
//						cout<<"K"<<endl;
						if ( ( *s[j].begin() ).second > i && !book[( *s[j].begin() ).second] ) {
							book[( *s[j].begin() ).second] = true;
							auto &[x, y] = last[( *s[j].begin() ).second];
							x = j;
							y = i;
						}

						s[j].erase( s[j].begin() );
//						cout<<"K"<<endl;
					}
				}
		}

//		cout<<">>"<<book[n]<<endl;

		if ( book[n] ) {
			cout << "YES" << endl;
			ll cur = n;

			while ( cur > 1 ) {
				ans.push_back( make_pair( last[cur].first, cur ) );
				cur = last[cur].second;
			}

			cout << ans.size() << endl;

			for ( int i = ans.size() - 1; i >= 0; i-- ) {
				if ( ans[i].first == 0 )
					cout << "Q ";

				if ( ans[i].first == 1 )
					cout << "K ";

				if ( ans[i].first == 2 )
					cout << "J ";

				cout << ans[i].second << endl;
			}
		} else
			cout << "NO" << endl;

	}

	return 0;
}

