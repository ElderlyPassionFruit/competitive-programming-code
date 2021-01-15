#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10, MAXLOG = 15;
int n, q;
vector <pair <int, int> > g[MAXN];
int tin[MAXN], tout[MAXN], timer = 0;
int dp[MAXN][MAXLOG];

void dfs(int v, int p)
{
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v])
	{
		if (i.first != p)
		{
			dfs(i.first, v);
		}
	}
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
	{
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	}
	return dp[v][0];
}



int SQ;
bool cmp(pair <int, int> a, pair <int, int> b)
{
	if (tin[a.first] / SQ != tin[b.first] / SQ)
	{
		return tin[a.first] < tin[b.first];
	}
	return tin[a.second] < tin[b.second];
}

vector <pair <int, int> > events;
map <pair <int, int>, bool > used;

void read()
{
	cin >> n >> q;
	for (int i = 1; i < n; i++)
	{
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		g[v].push_back({u, cost});
		g[u].push_back({v, cost});
	}
	dfs(0, 0);

	for (int i = 0; i < q; i++)
	{
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		if (tin[v] > tin[u])
			swap(v, u);
		evets.push_back({u, v});
		used[{u, v}] = false;
	}
	
	SQ = sqrt(n);
	sort(evets.begin(), evets.end(), cmp);
}

void run()
{
	int a = 0, b = 0;
	for (int i = 0; i < q; i++)
	{
		int u = events[i].first, v = events[i].second;
		int 
	}
}

void write()
{

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