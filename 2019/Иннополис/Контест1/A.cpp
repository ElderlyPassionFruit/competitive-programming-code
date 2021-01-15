#include <bits/stdc++.h>

using namespace std;

//#define int long long

const int MAXN = 51;

vector <int> g[MAXN], gr[MAXN], full[MAXN];
vector <vector <int> > comps;
int cost[MAXN];
vector <int> top_sort, help;
vector <bool> used;
int dp[MAXN];
int ans;
int n;

void dfs(int v)
{
	used[v] = true;
	for (auto i : g[v])
	{
		if(!used[i])
			dfs(i);
	}
	top_sort.push_back(v);
}

void dfs2(int v)
{
	used[v] = true;
	comps[comps.size() - 1].push_back(v);
	for (auto i : gr[v])
	{
		if (!used[i])
			dfs2(i);
	}
}

bool check_new()
{
	for (auto comp: comps)
	{
		int cnt = 0;
		for (auto i : comp)
		{
			for (auto v : g[i])
			{
				if (help[i] == help[v])
				{
					cnt++;
				}
			}
		}
		if (cnt > comp.size())
			return 0;
	}
	return 1;
}

void dfs_fans(int v)
{
	used[v] = true;
	for (auto i : full[v]){
		if (!used[i])
			dfs_fans(i);
	}
	top_sort.push_back(v);
}


void dfs_ans(int v)
{
	used[v] = true;
	dp[v] = cost[v];
	for (auto i : full[v])
	{
		if (!used[i]) {
			dfs_ans(i);
		}
		dp[v] = max(dp[v], dp[i] + cost[v]);
	}
}

void read()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			char x;
			cin >> x;
			if (i == j)
				continue;
			if (x == 'Y')
			{
				g[i].push_back(j);
				gr[j].push_back(i);
			}
		}
	}
}

void run()
{
	used.assign(MAXN, false);
	for (int i = 0; i < n; i++)
	{
		if (!used[i])
			dfs(i);
	}

	reverse(top_sort.begin(), top_sort.end());
	used.assign(MAXN, false);
	for (auto i : top_sort)
	{
		if (!used[i])
		{
			comps.push_back({});
			dfs2(i);
		}
	}
	
	help.assign(n, 0);
	for (int i = 0; i < comps.size(); i++)
	{
		for (auto j : comps[i])
		{
			help[j] = i;
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (auto v : g[i])
		{
			if (help[i] != help[v])
				full[help[i]].push_back(help[v]);
		}
	}
	
	for (int i = 0; i < comps.size(); i++)
	{
		cost[i] = (comps[i].size() > 1);
	}
	
	used.assign(MAXN, false);
	for (int i = 0; i < MAXN; i++)
	{
		if (!used[i])
			dfs_fans(i);
	}

	reverse(top_sort.begin(), top_sort.end());
	used.assign(MAXN, false);
	for (auto i : top_sort)
	{
		if (!used[i])
			dfs_ans(i);
	}

	if (check_new() == 0)
	{
		cout << -1 << endl;
		exit(0);
	}
}

void write()
{
	ans = 1;
	for (int i = 0; i < n; i++)
	{
		ans = max(ans, dp[i]);
	}
	cout << ans - 1 << endl;
}

void help_write()
{
	cout << endl << endl << endl;

	cout << "help: ";
	for (int i = 0; i < n; i++)
	{
		cout << help[i] << " ";
	}
	cout << endl;
	

	cout << "full:" << endl;
	for (int i = 0; i < MAXN; i++)
	{
		for (auto v : full[i])
			cout << i + 1 << " " << v + 1 << endl;
	}

	cout << "cost: ";
	for (int i = 0; i < n; i++)
		cout << cost[i] << " ";
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










