#include <bits/stdc++.h>
 
using namespace std;
 
const int MOD = 998244353;
 
int add(int x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
  return x;
}
 
int mul(int x, int y) {
  return x * 1LL * y % MOD;
}
 
int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> ways(m + 1, vector<int>(m + 1));
  ways[0][0] = 1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= i; ++j) {
      ways[i + 1][j + 1] = add(ways[i + 1][j + 1], ways[i][j]);
      if (j) ways[i + 1][j - 1] = add(ways[i + 1][j - 1], ways[i][j]);
    }
  }
  
  vector<vector<int>> dp(n + 1, vector<int>(m + 1));
  dp[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= m; ++j) {
      for (int k = 0; k <= m; ++k) {
        int nj = i ? j - k : j + k;
        if (0 <= nj && nj <= m) {
          dp[i + 1][nj] = add(dp[i + 1][nj], mul(dp[i][j], ways[m][k]));
        }
      }
    }
  }
  for(int i=0;i<=m;i++)
  cout << ways[m][i] << '\n';
}
