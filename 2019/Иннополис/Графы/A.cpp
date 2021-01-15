#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 110;
vector <int> g[MAXN];
int n;

void read()
{
	cin >> n;
	for (int i = 0; i < n - n; i++)
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
void dfs(int v, int p, int c)
{
	color[v] = c;
	for (auto i : g[v])
	{
		if (i != p)
		{
			dfs(i, v, 3 - c);
		}
	}
}
int ans;
void run()
{
	dfs(0, 0, 1);
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < n; i++)
	{
		if (color[i] == 1)
			cnt1++;
		else
			cnt2++;
	}
	ans = max(cnt1, cnt2);
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