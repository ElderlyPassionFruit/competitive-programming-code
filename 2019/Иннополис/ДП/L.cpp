#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MAXN = 1e5 + 10;
int dp[MAXN], cnt[MAXN];
vector <int> g[MAXN];
int n, m;
void read()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}
bool used[MAXN];
void dfs_down(int v, int p)
{
	used[v] = true;
	for (auto i : g[v])
	{
		if (i != p)
		{
			dfs_down(i, v);
			dp[v] += dp[i] + cnt[i] + 1;
			cnt[v] += cnt[i] + 1;
		}
	}
}

void dfs_up(int v, int p)
{
	used[v] = true;
	for (auto i : g[v])
	{
		if (i != p)
		{
			dp[i] = dp[v] - dp[i] - cnt[i] - 1 + cnt[v] - cnt[i] - 1 + dp[i] + 1;
			cnt[i] = cnt[v] - cnt[i] - 1 + cnt[i] + 1;
			dfs_up(i, v);
		}
	}
}

int ans1, cnt1;
void run()
{
	ans1 = 0;
	cnt1 = 0;
	for(int i = 0; i < n; i++)
	{
		if (!used[i])
			dfs_down(i, i);
	}
	
	for (int i = 0; i < n; i++)
		used[i] = false;


	/*cout << "dfs_down ";
	for (int i = 0; i < n; i++)
		cout << dp[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << cnt[i] << " ";
	cout << endl;
	*/


	for (int i = 0; i < n; i++)
	{
		if (!used[i])
			dfs_up(i, i);
	}
	

	/*cout << "dfs_up ";	
	for (int i = 0; i < n; i++)
		cout << dp[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << cnt[i] << " ";
	cout << endl;
	
	cout << endl;
*/
	for (int i = 0; i < n; i++)
	{
		ans1 += dp[i];
		cnt1 += cnt[i];
	}
}

void write()
{
	cout << cnt1 / 2 << endl << ans1 / 2 << endl;
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