#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10, MAXLOG = 20, INF = -1e18;
vector <int> g[MAXN];
int w[MAXN];
int n;

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], timer = 0;

int sz[MAXN], pred[MAXN], centr;
bool used[MAXN];

pair<int, int> tree[MAXN * 4];

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
			mx = max(mx, sz[i]);
		}
	}
	mx = max(mx, size - sz[v]);
	if (mx <= size / 2)
		centr = v;
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

pair <int, int> merge(pair <int, int> a, pair <int, int> b)
{
	if (a.first > b.first)
		return a;
	if (a.first < b.first)
		return b;
	if (a.second > b.second)
		return a;
	return b;
}

void upd(int v, int tl, int tr, int l, int r, pair<int, int> val)
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
	tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

pair <int, int> get(int v, int tl, int tr, int l, int r)
{
	if (tl >= r || tr <= l)
		return {0, 0};
	if (tl >= l && tr <= r)
		return tree[v];
	int tm = (tl + tr) / 2;
	return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
}

void read()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> w[i];
	for (int i = 1; i < n; i++)
	{
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	make();
}

void wr()
{
	cout << endl << endl << endl;
	cout << "pred: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << pred[i] << " ";
	}
	cout << endl;
}

int ans;
vector <pair <int, pair <int, int> > > fans[MAXN];


void run()
{
	ans = INF;
	for (int i = 0; i < n; i++)
	{
		int u = i;
		int last = -1;
		while (u != -1)
		{
			fans[u].push_back({w[i] , {dist(u, i), last}});
			last = u;
			u = pred[u];
		}
	}
//	wr();

//	cout << endl;
	for (int i = 0; i < n; i++)
	{
		sort(fans[i].begin(), fans[i].end());
//		cout << i << endl;
//		for (auto j : fans[i])
//			cout << j.first << " " << j.second.first << " " << j.second.second << endl;
//		cout << endl;
	}


	for (int i = 0; i < n; i++)
	{
		map <int, vector<int> > help;
		for (int j = 0; j < fans[i].size(); j++)
		{
			upd(1, 0, fans[i].size(), j, j + 1, {fans[i][j].second.first, fans[i][j].first});
			help[fans[i][j].second.second].push_back(j);
		}

	/*	cout << "help: " << endl;
		for (auto j : help)
		{
			cout << "j " << j.first << endl;
			for (auto pos: j.second)
			{
				cout << pos << " ";
			}
			cout << endl << endl;
		}
*/
		for (auto j : help)
		{
			for (auto pos: j.second)
			{
				upd(1, 0, fans[i].size(), pos, pos + 1, {0, 0});		
			}

			for (auto pos: j.second)
			{
				auto ax = get(1, 0, fans[i].size(), pos, fans[i].size());
				ans = max(ans, (ax.first + fans[i][pos].second.first) * min(ax.second, fans[i][pos].first));
			}

			for (auto pos: j.second)
			{
				upd(1, 0, fans[i].size(), pos, pos + 1, {fans[i][pos].second.first, fans[i][pos].first});		
			}			
		}

		for (int j = 0; j < fans[i].size(); j++)
		{
			upd(1, 0, fans[i].size(), j, j + 1, {0, 0});
		}
	}
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