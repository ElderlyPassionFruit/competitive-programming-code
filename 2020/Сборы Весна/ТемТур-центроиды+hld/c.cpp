#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n;
vector<int> g[MAXN];

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

bool used[MAXN];
int sz[MAXN];
int centr;

void dfs_centroid(int v, int p, int size) {
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) continue;
		dfs_centroid(i, v, size);
		sz[v] += sz[i];
		chkmax(mx, sz[i]);
	}
	chkmax(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

char ans[MAXN];

void solve(int v, int size, int h) {
	dfs_centroid(v, -1, size);
	v = centr;
	used[v] = true;
	ans[v] = 'A' + h;
	for (auto i : g[v]) {
		if (used[i]) continue;
		int fsz = sz[i];
		if (fsz > sz[v]) {
			fsz = size - sz[v];
		}
		solve(i, fsz, h + 1);
	}
}

void run() {
	solve(0, n, 0);
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
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