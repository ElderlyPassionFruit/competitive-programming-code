#include <bits/stdc++.h>

using namespace std;

#define int long long

void r()
{
	cout << "I can LIVE" << endl;
}

const int MAXN = 1e5 + 10;
const int MAXLOG = 15;
int n;
int w[MAXN];
vector <int> g[MAXN];

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0, h[MAXN];

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
		return u;
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return dp[v][0];
}

int dist(int v, int u)
{
	return h[v] + h[u] - 2*h[lca(v, u)];
}

int sz[MAXN], pred[MAXN];
bool used[MAXN];
int center;
void dfs_centroid(int v, int p, int size)
{
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v])
	{
		if (!used[i] && i != p)
		{
			dfs_centroid(i, v, size);
			sz[v] += sz[i];
			mx = max(sz[i], mx);
		}
	}
	mx = max(mx, size - sz[v]);
	if (mx <= size / 2)
		center = v;
}

void find_centroid(int v, int p, int size)
{
	dfs_centroid(v, v, size);
	int u = center;
	used[u] = true;
	pred[u] = p;

	for (auto i : g[u])
	{
		if (!used[i])
		{
			int fsz = sz[i];
			if (sz[i] > sz[u])
				fsz = size - sz[u];
			find_centroid(i, u, fsz);
		}
	}
}

void make()
{
	dfs_lca(0, 0, 0);
	find_centroid(0, -1, n);
}


pair <int, int> tree[4 * MAXN];

void upd(int v, int tl, int tr, int l, int r, pair <int, int> val)
{
	if (tl >= r || tr <= l)
		return;
	if (tl == l && tr == r)
	{
		tree[v] = val;
		return;
	}
	int tm = (tl + tr) / 2;
	upd(v * 2, tl, tm, l, r, val);
	upd(v * 2 + 1, tm, tr, l, r, val);
	tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
}

pair <int, int> get(int v, int tl, int tr, int l, int r)
{
	if (tl >= r || tr <= l)
		return {0, 0};
	if (tl >= l && tr <= r)
		return tree[v];
	int tm = (tl + tr) / 2;
	return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
}


void read()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> w[i];
	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
}

int ans;

vector <pair <int, pair <int, int> > > fans[MAXN];


void run()
{
	make();

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
	read();
	run();
	write();
	return 0;
}