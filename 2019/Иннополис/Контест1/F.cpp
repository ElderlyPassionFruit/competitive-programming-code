#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MAXN = 2*1e3 + 10;
int n, k;
vector <int> g[MAXN];

int cnt;
int must;

void dfs(int v, int p, int length)
{
	if (length > must)
		cnt++;
	for (auto i : g[v])
	{
		if (i != p)
			dfs(i, v, length + 1);
	}
}

int solve(int v){
	vector <pair <int, int> > cnt1;
	must = k / 2;
	for (auto i : g[v])
	{
		cnt = 0;
		dfs(i, v, 1);
		cnt1.push_back({cnt, i});
	}
	
	vector <pair <int, int> > cnt2;
	
	must = (k + 1) / 2;
	
	for (auto i : g[v])
	{
		cnt = 0;
		dfs(i, v, 1);
		cnt2.push_back({cnt, i});
	}

	int ans = 1e18;
	for (auto i : cnt2)
	{
		int fans = i.first;
		for (auto j : cnt1)
		{
			if (j.second == i.second)
				continue;
			fans += j.first;
		}
		ans = min(ans, fans);
	}

	/*cout << "123\n";
	for (auto i : cnt1)
		cout << i.first << " ";
	cout << endl;
	for (auto i : cnt2)
		cout << i.first << " ";
	cout << endl;*/
	return ans;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++){
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	int ans = 1e18;
	for (int i = 0; i < n; i++)
	{
		ans = min(ans, solve(i));
	}
	cout << ans << endl;
	return 0;
}