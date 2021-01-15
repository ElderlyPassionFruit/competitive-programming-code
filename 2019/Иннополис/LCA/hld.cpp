#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e6 + 10;
int tree[MAXN * 4];

int get(int v, int tl, int tr, int l, int r)
{
	if (tl >= r || tr <= l)
		return 0;
	if (tl >= l && tr <= r)
		return tree[v];
	int tm = (tl + tr) / 2;
	return get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
}

void upd(int v, int tl, int tr, int l, int r, int val)
{
	if (tl >= r || tr <= l)
		return;
	if (tl == l && tr == r)
	{
		tree[v] += val;
		return;
	}
	int tm = (tl + tr) / 2;
	upd(v * 2, tl, tm, l, r, val);
	upd(v * 2 + 1, tm, tr, l, r, val);
	tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

const int MAXLOG = 20;
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN];
vector <int> g[MAXN];
int timer = 0;

void dfs(int v, int p)
{
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v])
		if (i != p)
			dfs(i, v);
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
int n;
void read()
{
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
}

void wr()
{
	cout << endl;
	cout << "tree:" << endl;
	for (int i = 0; i < 2 * n; i++)
	{
		cout << get(1, 0, 2 * n, i, i + 1) << " ";
	}
	cout << endl;
}

vector <int> ans;
int mod[MAXN];
void run()
{
	dfs(0, 0);
	int m;
	cin >> m;
	cout << endl;
	while (m--)
	{
		char type;
		cin >> type;
		if (type == '+')
		{
			int v, u, d;
			cin >> v >> u >> d;
			v--;
			u--;
			int l = lca(v, u);
			upd(1, 0, 2 * n, tin[l], tin[l] + 1, - 2 * d);
			upd(1, 0, 2 * n, tin[v], tin[v] + 1, d);
			upd(1, 0, 2 * n, tin[u], tin[u] + 1, d);
			mod[l] += d;
		}
		else
		{
			int v;
			cin >> v;
			v--;
			int ax = get(1, 0, 2 * n, tin[v], tout[v] + 1);
	//		cout << "v = " << v << ", get = " << ax << ", mod = " << mod[v] << endl;
			ax += mod[v];
			ans.push_back(ax); 
		}
	//	wr();
	}
}

void write()
{
	for (auto i : ans)
		cout << i << endl;
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