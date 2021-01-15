#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

char ans[MAXN];

int sz[MAXN], used[MAXN], centr;

void dfs_centr(int v, int p, int size) {
	sz[v] = 1;
	int m = 0;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_centr(i, v, size);
			sz[v] += sz[i];
			chkmax(m, sz[i]);
		}
	}
	chkmax(m, size - sz[v]);
	if (m <= size / 2) {
		centr = v;
	}
}

void find_centr(int v, int size, int len) {
	dfs_centr(v, -1, size);
	int u = centr;
	used[u] = true;
	ans[u] = len + 'A';
	for (auto i : g[u]) {
		if (!used[i]) {
			int fsz = sz[i];
			if (fsz > sz[u])
				fsz = size - sz[u];
			find_centr(i, fsz, len + 1);
		}
	}
}

void run() {
	find_centr(0, n, 0);
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	cout << endl;
}

signed main() {
#ifdef LOCAL
    freopen("in", "r", stdin);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}