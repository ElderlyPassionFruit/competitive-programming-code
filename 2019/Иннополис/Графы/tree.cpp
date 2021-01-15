#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MAXN = 1e5 + 10, MAXLOG = 15;
vector <int> g[MAXN];
int tin[MAXN], tout[MAXN], dp[MAXN][MAXLOG], h[MAXN], timer = 0;
int n;

void dfs_lca(int v, int p, int len)
{
	h[v] = len++;
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v])
		if (i != p)
			dfs_lca(i, v, len);
	tout[v] = timer++;
}

bool is_upper(int v, int u)
{
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u)
{
	if (is_upper(v, u))
		return v;
	if (is_upper(u, v))
		return v;
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return dp[v][0];
}

int dist(int v, int u)
{
	return h[v] + h[u] - 2 * h[lca(v, u)];
}

int centr;
int sz[MAXN], pred[MAXN];
bool used[MAXN];

void dfs_centroid(int v, int p, int size)
{
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v])
	{
		if (i != p && !used[i])
		{
			dfs_centroid(i, v, size);
			mx = max(mx, sz[i]);
			sz[v] += sz[i];
		}
	}
	if (sz[v] != size)
	{
		mx = max(mx, size - sz[v]);
	}
	if (mx < size / 2)
	{
		centr = v;
	}
}

void find_centroid(int v, int p, int size)
{
	dfs_centroid(v, -1, size);
	int u = centr;
	used[u] = true;
	pred[u] = p;
	for (auto i : g[u])
	{
		if (!used[i])
		{
			int fsz = sz[i];
			if (fsz > sz[u])
			{
				fsz = size - sz[u];
			}
			dfs_centroid(i, u, fsz);
		}
	}
}

void make()
{
	dfs_lca(0, 0, 0);
	find_centroid(0, -1, n);
}

int cost[MAXN];
void read()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> cost[i];
	}

	for (int i = 0; i < n - 1; i++)
	{
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	make();
}

int ans = 0;
vector <pair <int, int> > fans[MAXN];
void run()
{
	for (int i = 0; i < n; i++)
	{
		int u = i;
		while (u != -1)
		{
			fans[u].push_back({dist(u, i), u});
			u = pred[u];
		}
	}
	for (int i = 0; i < n; i++)
	{
		sort(fans[i].begin(), fans[i].end());
		reverse(fans[i].begin(), fans[i].end());
		for (int j = 1; j < fans[i].size(); j++)
		{
			if (lca(fnas[i][0].second, fnas[i][j].second) == i)
			{
				int d = fnas[i][0].first + fans[i][j].first;
				int 
			}
		}
	}
}

void write()
{
	cout << ans;
}

void clear()
{
	for (int i = 0; i < n; i++)
	{
		tin[i] = 0;
		tout[i] = 0;
		h[i] = 0;
		pred[i] = 0;
		g[i].clear();
		used[i] = false;
		sz[i] = 0;
		for (int j = 0; j < MAXLOG; j++)
			dp[i][j] = false;
	}
	timer = 0;
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