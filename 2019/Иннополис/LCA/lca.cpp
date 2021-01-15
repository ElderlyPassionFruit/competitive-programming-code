#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MAXN = 5*1e5 + 10;
const int MAXLOG = 20;
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0, h[MAXN];
int min_cost[MAXN][MAXLOG];

vector <pair <int, int> > g[MAXN];

void dfs(int v, int p, int len, int cost){
	h[v] = len;
	
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	
	min_cost[v][0] = cost;
	for (int i = 1; i < MAXLOG; i++)
		min_cost[v][i] = min(min_cost[v][i - 1], min_cost[dp[v][i - 1]][i - 1]);

	tin[v] = timer++;
	for (auto i : g[v])
	{
		if (i.first != p)
		{
			dfs(i.first, v, len + i.second, i.second);
		}
	}
	tout[v]= timer++;
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

int get_ans(int v, int u)
{
	int x = lca(v, u);
	int ans = 1e18;
	for (int i = MAXLOG - 1; i >= 0; i--)
	{
		if (!is_upper(dp[v][i], x))
		{
			ans = min(ans, min_cost[v][i]);
			v = dp[v][i];
		}
	}
	if (v != x)
		ans = min(ans, min_cost[v][0]);
	for (int i = MAXLOG - 1; i >= 0; i--)
	{	
		if (!is_upper(dp[u][i], x))
		{
			ans = min(ans, min_cost[u][i]);
			u = dp[u][i];
		}
	}
	if (u != x)
		ans = min(ans, min_cost[u][0]);
	return ans;
}



int n, m;
vector <pair <int, int> > events;
void read()
{	
	int k;
	cin >> k;
	n = 0;
	m = 0;
	for (int i = 0; i < k; i++)
	{
		string s;
		cin >> s;
		if (s == "ADD")
		{
			n++;
			int v, u;
			cin >> v >> u;
			v--;
			u--;
			g[u].push_back({v, 1});
			g[v].push_back({u, 1});
		}
		if (s == "GET")
		{
			m++;
			int v, u;
			cin >> v >> u;
			v--;
			u--;
			events.push_back({u, v});
		}		
	}
	/*cin >> n;
	for (int i = 1; i < n; i++)
	{
		int p, cost;
		cin >> p >> cost;
		p--;
		g[i].push_back({p, cost});
		g[p].push_back({i, cost});
	}*/
}


void run()
{
	for (int i = 0; i < MAXN; i++)
	{
		for (int j = 0; j < MAXLOG; j++)
		{
			min_cost[i][j] = 1e18;
		}
	}
	dfs(0, 0, 0, 1e18);
	for (int i = 0; i < m; i++)
	{
		int v = events[i].first;
		int u = events[i].second;	
		cout << lca(u, v) + 1 << endl;
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