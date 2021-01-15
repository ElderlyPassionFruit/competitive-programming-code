#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 110;
vector <int> g[MAXN];
int n;

void read()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		if (x == 0)
			continue;
		x--;
		g[x].push_back(i);
		g[i].push_back(x);
	}
}

int color[MAXN];
int dp[MAXN][2];

void dfs(int v, int p)
{
	dp[v][1] = 1;
	for (auto i : g[v])
	{
		if (i != p)
		{
			dfs(i, v);
			dp[v][0] += max(dp[i][0], dp[i][1]);
			dp[v][1] += dp[i][0];
		}
	}
}

int ans;
void run()
{
	dfs(0, 0);
	/*cout << endl;
	cout << cnt1 << " " << cnt2 << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "i = " << i + 1 << endl;
		for (auto j : g[i])
		{
			cout << j << " ";
		}
		cout << endl;
	}*/
	ans = max(dp[0][0], dp[0][1]);
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