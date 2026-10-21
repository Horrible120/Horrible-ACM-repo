#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
	int s = 1;
	while(b) {
		if(b & 1) s = 1ll * s * a % mod;
		a = 1ll * a * a % mod, b >>= 1;
	}
	return s;
}

bool Mbe;

constexpr int N = 2.5e6 + 5;

int n, a, b, c, d, fc[N], ifc[N];
int bin(int n, int m) {
	return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void solve() {
	cin >> n;
	for(int i = fc[0] = 1; i < N; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
	ifc[N - 1] = ksm(fc[N - 1], mod - 2);
	for(int i = N - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
	for(int i = 0; i <= n; i++) {
		int x;
		cin >> x;
		if(i < n) {
			int coef = 1ll * bin(n - 1, i) * x % mod;
			addt(a, i & 1 ? coef : mod - coef);
		}
		if(i) {
			int coef = 1ll * bin(n - 1, i - 1) * x % mod;
			addt(b, i & 1 ? mod - coef : coef);
		}
	}
	for(int i = 0; i <= n; i++) {
		int x;
		cin >> x;
		if(i) {
			int coef = 1ll * bin(n - 1, i - 1) * x % mod;
			addt(d, i & 1 ? mod - coef : coef);
		}
	}
	
	cout << 1ll * (d + mod - b) * ksm(b + mod - a, mod - 2) % mod << "\n";
}

bool Med;
int main() {
#ifdef ALEX_WEI
	FILE *IN = freopen("1.in", "r", stdin);
	FILE *OUT = freopen("1.out", "w", stdout);
#endif
	fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1;
	// cin >> T;
	while(T--) solve();
	cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
	return 0;
}
/*
g++ C.cpp -o C -std=c++14 -O2 -DALEX_WEI
*/
