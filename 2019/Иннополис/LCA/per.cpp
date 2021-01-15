#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MAXN = 1e6 + 10;

vector <int> g[MAXN];
int root;
int color[MAXN];
int n;

void read()
{
	cin >> n;	
	for (int i = 0; i < n; i++)
	{
		int p, c;
		cin >> p >> c;
		color[i] = c;
		if (p == 0)
		{
			root = i;
			continue;
		}
		p--;
		g[i].push_back(p);
		g[p].push_back(i);
	}
}

int ans[MAXN];
int sz[MAXN];

void dfs_help(int v, int p)
{
	sz[v] = 1;
	for (auto i : g[v])
	{
		if (i != p)
		{
			dfs_help(i, v);
			sz[v] += sz[i];
		}
	}
}

void mer(unordered_set <int> &a, unordered_set <int> &b)
{
	for (auto i : b)
		a.insert(i);
}

unordered_set <int> dfs(int v, int p)
{
	//cout << "v = " << v << endl;
	int pos = -1;
	int size = 0;
	for (auto i : g[v])
	{
		if (i != p && sz[i] > size)
		{
			size = sz[i];
			pos = i;
		}
	}
	unordered_set <int> res;
	if (pos != -1)
	{
		res = dfs(pos, v);
	}
	res.insert(color[v]);

	for (auto i : g[v])
	{
		if (i != p && i != pos)
		{
			unordered_set <int> s = dfs(i, v);
			mer(res, s);
		}
	}
	ans[v] = res.size();
	return res;
}


void run()
{
	dfs_help(root, root);
	
	//cout << "puhh" << endl;
	dfs(root, -1);

	//cout << "puhh" << endl;
}

void write()
{
	for (int i = 0; i < n; i++)
	{
		cout << ans[i] << " ";
	}
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