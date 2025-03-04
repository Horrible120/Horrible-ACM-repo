#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 3e5 + 5;
int64_t sum[MAXN], ans[MAXN];
vector<int> yy;
vector<tuple<int, int, int>> vec;
vector<tuple<int, int, int, int>> q;

inline int lowbit(int x) { return x & (-x); }

void add(int pos, int64_t x)
{
	for (; pos < MAXN; pos += lowbit(pos))
		sum[pos] += x;
}

int64_t query_presum(int pos)
{
	int64_t ans = 0;
	for (; pos > 0; pos -= lowbit(pos))
		ans += sum[pos];
	return ans;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, x1, x2, y1, y2, p;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> x1 >> y1 >> p;
		yy.push_back(y1);
		vec.emplace_back(x1, y1, p);
	}
	sort(vec.begin(), vec.end());
	for (int i = 0; i < m; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		yy.push_back(y1 - 1), yy.push_back(y2);
		q.emplace_back(x1 - 1, y1 - 1, 1, i);
		q.emplace_back(x1 - 1, y2, -1, i);
		q.emplace_back(x2, y1 - 1, -1, i);
		q.emplace_back(x2, y2, 1, i);
	}
	sort(q.begin(), q.end());
	sort(yy.begin(), yy.end());
	yy.erase(unique(yy.begin(), yy.end()), yy.end());
	int cur = 0;
	for (auto [x, y, c, id] : q)
	{
		y = lower_bound(yy.begin(), yy.end(), y) - yy.begin() + 1;
		while (cur < n)
		{
			auto [_x, _y, p] = vec[cur];
			if (_x > x)
				break;
			_y = lower_bound(yy.begin(), yy.end(), _y) - yy.begin() + 1;
			add(_y, p), ++cur;
		}
		ans[id] += c * query_presum(y);
	}
	for (int i = 0; i < m; i++)
		cout << ans[i] << "\n";
	
	return 0;
}

