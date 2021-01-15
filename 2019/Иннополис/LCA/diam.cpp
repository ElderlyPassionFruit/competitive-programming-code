#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2*1e5 + 10, MAXLOG = 20;
vector <int> g[MAXN];
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], timer = 0; 
void dfs(int v, int p, int len)
{
	h[v] = len++;
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v])
		if (i != p)
			dfs(i, v, len);
	tout[v] = timer++;
}

bool is_upper(int v, int u)
{
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u)
{
	if (is_upper(v, u)) return v;
	if (is_upper(u, v)) return u;
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
    return dp[v][0];
}

int dist(int v, int u)
{
	return h[v] + h[u] - 2*h[lca(v, u)];
}

int n;
void read()
{
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int p;
		cin >> p;
		p--;
		g[i].push_back(p);
		g[p].push_back(i);
	}
	dfs(0, 0, 0);
}
int ans[MAXN];
void run()
{
	int s = 0, f = 0;
	int d = 0;
	for (int i = 0; i < n - 1; i++)
	{
		int n_s = s;
		int n_f = f;
		if (d < dist(i + 1, s))
		{
			n_s = s;
			n_f = i + 1;
			d = dist(i + 1, s);
		}
		if (d < dist(i + 1, f))
		{
			n_s = i + 1;
			n_f = f;
			d = dist(i + 1, f);
		}
		s = n_s;
		f = n_f;
		ans[i] = d;
	}
}

void write()
{
	for (int i = 0; i < n - 1; i++)
		cout << ans[i] << " ";
	cout << endl;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}