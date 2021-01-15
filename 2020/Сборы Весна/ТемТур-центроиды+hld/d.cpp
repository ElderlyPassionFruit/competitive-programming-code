#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10, MAXLOG = 17;
int n;
vector<int> g[MAXN];
int a[MAXN];

void read() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int u;
		cin >> u;
		int v = i;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

bool used[MAXN];
int sz[MAXN];
int centr;
int dist[MAXN][MAXLOG];
int h[MAXN];

void dfs_centroid(int v, int p, int size, int H, int len) {
	if (H != -1) {
		dist[v][H] = len;
	}
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) continue;
		dfs_centroid(i, v, size, H, len + 1);
		sz[v] += sz[i];
		chkmax(mx, sz[i]);
	}
	chkmax(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

int par[MAXN];

void build(int v, int p, int size, int H) {
	used[v] = true;
	par[v] = p;
	h[v] = H;
	for (auto i : g[v]) {
		if (used[i]) continue;
		int fsz = sz[i];
		if (fsz > sz[v]) {
			fsz = size - sz[v];
		}
		dfs_centroid(i, -1, fsz, H, 1);
		build(centr, v, fsz, H + 1);
	}
}

vector<pair<int, int>> have[MAXN];

void build() {
	dfs_centroid(0, -1, n, -1, 0);
	build(centr, -1, n, 0);

	for (int v = 0; v < n; v++) {
		int now = v;
		int H = h[v];
		while (now != -1) {
			have[now].push_back({a[v], dist[v][H]});
			H--;
			now = par[now];
		}
	}
	for (int i = 0; i < n; i++) {
		sort(all(have[i]));
	}
}

int get(int v, int c) {
	int now = v;
	int H = h[v];
	int ans = n + 1;
	while (now != -1) {
		int pos = lower_bound(all(have[now]), make_pair(c, -1)) - have[now].begin();
		if (pos < (int)have[now].size() && have[now][pos].first == c) {
			chkmin(ans, dist[v][H] + have[now][pos].second);
		}
		H--;
		now = par[now];
	}
	if (ans == n + 1) {
		ans = -1;
	}
	return ans;
}

void run() {
	build();
	int q;
	cin >> q;
	while (q--) {
		int v, c;
		cin >> v >> c;
		cout << get(v, c) << " ";
	}
	cout << endl;
}

void write() {
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