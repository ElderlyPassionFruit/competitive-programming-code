#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e3 + 10;
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

int sz[MAXN];

void dfs_sz(int v, int p) {
	sz[v] = 1;
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_sz(i, v);
		sz[v] += sz[i];
	}
}

int ans;

vector<int> path;
int pos_mid = 0;

void recalc() {
	int n = path.size();
	while (pos_mid < n / 2)
		pos_mid++;
	while (pos_mid > n / 2)
		pos_mid--;
}

bool check() {
	int n = path.size();
	if (n == 1) return false;
	if (n & 1) {
		return sz[path[0]] - sz[path[pos_mid]] == sz[path[pos_mid + 1]];
	}
	else {
		return sz[path[0]] - sz[path[pos_mid]] == sz[path[pos_mid]];
	}
}

void dfs_calc(int v, int p) {
	path.push_back(v);
	recalc();
	if (check()) ans++;
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_calc(i, v);
	}
	path.pop_back();
	recalc();
}

void run() {
	ans = 0;
	for (int i = 0; i < n; i++) {
		dfs_sz(i, -1);
		dfs_calc(i, -1);
	}
}

void write() {
	assert(ans % 2 == 0);
	cout << ans / 2 << endl;
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