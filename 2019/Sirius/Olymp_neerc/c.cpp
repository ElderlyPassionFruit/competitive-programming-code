#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MAXN = 5*1e5 + 10;
set <int> g[MAXN];
int n, m;

int root;
bool used[MAXN];

void dfs_root(int v){
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i])
			dfs_root(i);
	}
	root = v;
}
void check(int v, int p) {
	used[v] = true;
	for (auto i : g[v]) {
		if (i != p && used[i]) {
			cout << "No\n";
			exit(0);
		}
		if (!used[i])
			check(i, v);
	}
}

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].insert(v);
	}
}
int ans[MAXN];
void run() {
	for (int i = 0; i < n; i++) {
		if (!used[i])
			dfs_root(i);
	}
	for (int i = 0; i < n; i++) {
		used[i] = false;
	}
	check(root, -1);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (used[i]) cnt++;
	}
	if (cnt != n) {
		cout << "No\n";
		exit(0);
	}
	ans[root + 1] = -1;
	for (int i = 0; i < n; i++) {
		for (auto j : g[i]) {
			ans[j + 1] = i + 1;
		}
	}
}

void write() {
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}