#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, k, a[3010], pre[3010][3010], suf[3010][3010], ans[3010], vis[3010];
char ch[3010];
signed main(){
	scanf ("%lld", &t);
	while (t --){
		scanf ("%lld%lld%s", &n, &k, ch+1);
		for (int i=1; i<=n; i++){
			a[i] = ch[i] - '0';
			ans[i] = vis[i] = 0;
		}
		a[n+1] = 0;
		for (int i=0; i<=k; i++) suf[n+1][i] = 0;
		for (int i=1; i<=n; i++){
			int now = 0, x = i-1;
			for (int j=0; j<=k; j++){//找i右边第j+1个0的位置，没有就是n+1
				while (now < j+1 && x <= n){
					x ++;
					if (a[x] == 0) now ++;
				}
				suf[i][j] = x - i;
			}
		}
		for (int i=n; i>=1; i--){
			for (int j=0; j<=k; j++){
				suf[i][j] = max(suf[i][j], suf[i+1][j]);
			}
		}
		for (int i=n; i>=1; i--){
			int now = 0, x = i+1;
			for (int j=0; j<=k; j++){
				while (now < j+1 && x >= 1){
					x --;
					if (a[x] == 0) now ++;
				}
				pre[i][j] = i - x;
			}
		}
		for (int i=1; i<=n; i++){
			for (int j=0; j<=k; j++){
				pre[i][j] = max(pre[i][j], pre[i-1][j]);
			}
		}
		vis[0] = 1;
		ans[0] = max(pre[n][k], suf[1][k]);
		for (int i=1; i<=n; i++){
			int tot = 0;
			for (int j=i; j<=n; j++){
				if (a[j] == 1) tot ++;
				if (tot > k) break;
				ans[j-i+1] = max(ans[j-i+1], suf[j+1][k-tot]);
				ans[j-i+1] = max(ans[j-i+1], pre[i-1][k-tot]);
				vis[j-i+1] = 1;
			}
		}
		for (int i=1; i<=n; i++){
			int now = 0;
			for (int j=0; j<=n; j++){
				if (!vis[j]) continue;
				now = max(now, i*j + ans[j]);
			}
			printf ("%lld ", now);
		}
		puts ("");
	}
	return 0;
}

