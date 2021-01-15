#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 300;
int n, k;
vector<int> g[MAXN], mt;
vector<char> used;
 
bool dfs(int v) 
{
	if (used[v])  
		return false;
	used[v] = true;
	for (auto to : g[v])
	{
		if (mt[to] == -1 || dfs(mt[to])) 
		{
			mt[to] = v;
			return true;
		}
	}
	return false;
}
 
signed main() 
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("pairs.in", "r", stdin);
	freopen("pairs.out", "w", stdout);	
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		int v;
		while (cin >> v)
		{
			if (v == 0)
				break;
			v--;
			g[i].push_back(v);
		}
	}
 
	mt.assign (k, -1);
	for (int v = 0; v < n; v++)
	{
		used.assign(n, false);
		dfs(v);
	}
 
 	vector <pair <int, int> > ans;
	for (int i = 0; i < k; i++)
		if (mt[i] != -1)
			ans.push_back({mt[i] + 1, i + 1});

	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i.first << " " << i.second << endl;
	return 0;
}