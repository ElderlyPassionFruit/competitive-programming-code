#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 1e5 + 10;
vector<pair <int, int> > g[MAXN];
int used[MAXN];
int n, m;
void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, len, lum;
		cin >> u >> v >> len >> lum;
		u--;
		v--;
		g[u].push_back({v, lum});
		g[v].push_back({u, lum});
	}
}

void dfs(int v) {
	for (auto i : g[v]) {
		if (used[i.first] > i.second && i.second >= used[v]) {
			used[i.first] = i.second;
			dfs(i.first);
		}
	}
}

const int INF = 1e9 + 10;

void run() {
	for (int i = 0; i < n; i++)
		used[i] = INF;
	used[0] = 0;
	dfs(0);
	if (used[1] == INF) {
		cout << false;
		exit(0);
	}
	for (int i = 2; i < n; i++)
		used[i] = INF;
	used[0] = INF;
	dfs(1);
	if (used[0] == INF) {
		cout << false;
		exit(0);
	}
	cout << true;
	exit(0);
}

void write() {

}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}