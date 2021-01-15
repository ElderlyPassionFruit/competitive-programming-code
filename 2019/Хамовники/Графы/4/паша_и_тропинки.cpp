#include <bits/stdc++.h>

using namespace std;
#define int long long


const int MAXN = 1e5 + 10;
int dp[MAXN][2], cnt[MAXN][2];
vector <pair <int, pair <int, int> > > g[MAXN];
int n;

void read()
{
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--;
		b--;
		g[a].push_back({b, {c, d}});
		g[b].push_back({a, {c, d}});
	}
}

void dfs_down(int v, int p)
{
	for (auto i : g[v])
	{
		int u = i.first;
		int cost = i.second.first;
		int type = i.second.second;
		if (u != p)
		{
			dfs_down(u, v);
			if (type == 0)
			{
				dp[v][0] += dp[u][0] + cnt[u][0] * cost + cost;
				cnt[v][0] += cnt[u][0] + 1;

				dp[v][1] += dp[u][1] + cnt[u][1] * cost;
				cnt[v][1] += cnt[u][1];
			}
			else if (type == 1)
			{
				dp[v][1] += dp[u][0] + cnt[u][0] * cost;
				dp[v][1] += dp[u][1] + cnt[u][1] * cost + cost;
				cnt[v][1] += cnt[u][0];
				cnt[v][1] += cnt[u][1] + 1;
			}
		}
	}
}

void dfs_up(int v, int p)
{
	for (auto i : g[v])
	{
		int u = i.first;
		int cost = i.second.first;
		int type = i.second.second;
		if (u != p)
		{
			int x;
			if (type == 0)
			{
				x = dp[v][0] - dp[u][0] - cnt[u][0] * cost - cost + (cnt[v][0] - cnt[u][0] - 1) * cost + cost;
				dp[u][0] += x;
				x = cnt[v][0] - cnt[u][0] - 1 + 1;
				cnt[u][0] += x;

				x = dp[v][1] - dp[u][1] - cnt[u][1] * cost + (cnt[v][1] - cnt[u][1]) * cost;
				dp[u][1] += x;
				x = cnt[v][1] - cnt[u][1];
				cnt[u][1] += x;
			}
			else if (type == 1)
			{
				int y = dp[v][0] + cnt[v][0] * cost;
			//	cout << "ето от dp[v][0] " << y << endl;
				x = dp[v][1] - dp[u][1] - dp[u][0] - (cnt[u][1] + cnt[u][0] + 1) * cost + (cnt[v][1] - (cnt[u][1] + cnt[u][0] + 1)) * cost + cost;
			//	cout << "ето от dp[v][1] " << x << endl;
				dp[u][1] += x;
				dp[u][1] += y;
				x = cnt[v][1] - cnt[u][0] - cnt[u][1] - 1 + 1;
				cnt[u][1] += x;
				cnt[u][1] += cnt[v][0];
			}
			dfs_up(u, v);
		}
	}
}

long double ans;
void run()
{
	dfs_down(0, 0);
	/*cout << "немного дебага\n";
	for (int i = 0; i < n; i++)
	{
		cout << i << " " << dp[i][1] << " " << cnt[i][1] << endl;
	}
	cout << endl;
	*/dfs_up(0, 0);
	/*cout << "ещё немного дебага\n";
	for (int i = 0; i < n; i++)
	{
		cout << i << " " << dp[i][1] << " " << cnt[i][1] << endl;
	}
	cout << endl;
	*/ans = 0;
	int full_cnt = 0;
	for (int i = 0; i < n; i++)
	{
		ans += dp[i][1];
		full_cnt += cnt[i][1];
	}
	if (full_cnt == 0)
	{
		ans = 0;
		return;
	}
	ans = ans / full_cnt;
}

void write()
{
	cout << ans << endl;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(20);
	read();
	run();
	write();
	return 0;
}


























