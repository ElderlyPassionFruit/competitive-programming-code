#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 2e5 + 10;
vector<pair<int, int>> g[MAXN];

int color[MAXN];

void dfs(int v, int c) {
	color[v] = c;
	for (auto i : g[v]) {
		if (!color[i.first]) {
			if (i.second == 0)
				dfs(i.first, c);
			else
				dfs(i.first, 3 - c);
		}
		if (i.second == 0 && color[v] != color[i.first]) {
			cout << "NO\n";
			exit(0);
		}
		if (i.second == 1 && color[v] == color[i.first]) {
			cout << "NO\n";
			exit(0);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, t;
		cin >> u >> v >> t;
		u--;
		v--;
		t--;
		g[u].push_back({v, t});
		g[v].push_back({u, t});
	}
	for (int i = 0; i < n; i++) {
		if (!color[i])
			dfs(i, 1);
	}
	cout << "YES\n";
	for (int i = 0; i < n; i++)
		cout << color[i] << " ";
	cout << endl;
	return 0;
}