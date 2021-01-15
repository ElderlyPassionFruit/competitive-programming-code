#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MAXN = 1e5 + 10;
set <int> g[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		g[v].insert(u);
		g[u].insert(v);
	}
}

int used[MAXN];
bool flag;
void dfs(int v, int c) {
	used[v] = c;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs(i, 3 - c);
		}
		else if (used[i] == c) {
			flag = false;
		} 
	}
}

void run() {
	flag = true;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i, 1);
		}
	}
}

void write() {
	if (flag) {
		cout << "YES\n";
		for (int i = 0; i < n; i++) {
			cout << used[i] << " ";
		}
		cout << endl;
	}
	else {
		cout << "NO\n";
	}
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