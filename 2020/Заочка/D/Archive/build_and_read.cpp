//#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,mmx,avx2,popcnt")

#include <bits/stdc++.h>

using namespace std;
//#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment{
	int l, r;
	segment() {}
	segment(int a, int b) {
		l = a, r = b;
	}
};

bool operator<(const segment & a, const segment & b) {
	return tie(a.l, a.r) < tie(b.l, b.r); 
}

const int MAXN = 1e6 + 10;
vector<int> g[MAXN];
int n, k;
vector<segment> have[MAXN];

void read() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		have[i].resize(k);
		for (auto &j : have[i])
			scanf("%d", &j.l);
		for (auto &j : have[i])
			scanf("%d", &j.r);
		for (auto &j : have[i]) {
			if (j.l > j.r) {
				swap(j.l, j.r);
			}
		}
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int sz_coords = -1;

void build_coords() {
	for (int i = 0; i < k; i++) {
		vector<int> coord(2 * n);
		for (int j = 0; j < n; j++) {
			coord[2 * j] = have[j][i].l;
			coord[2 * j + 1] = have[j][i].r;
		}				
		sort(all(coord));
		coord.resize(unique(all(coord)) - coord.begin());
		chkmax(sz_coords, coord.size());
		for (int j = 0; j < n; j++) {
			have[j][i].l = lower_bound(all(coord), have[j][i].l) - coord.begin();
			have[j][i].r = lower_bound(all(coord), have[j][i].r) - coord.begin();
		}
	}
}

const int MAXLOG = 21;
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0, h[MAXN];

void dfs_lca(int v, int p, int len) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	h[v] = len++;
	for (auto i : g[v]) {
		if (i != p) {
			dfs_lca(i, v, len);
		}
	}
	tout[v] = timer++;
}

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (is_upper(v, u)) return v;
	if (is_upper(u, v)) return u;
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return dp[v][0];
}

int get_dist(int v, int u) {
	return h[v] + h[u] - 2 * h[lca(v, u)];
}

int par[MAXN], h_centr[MAXN], sz[MAXN];
bool used[MAXN];
int centr;

void dfs_centr(int v, int p, int size) {
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v]) {
		if (!used[i] && i != p) {
			dfs_centr(i, v, size);
			sz[v] += sz[i];
			chkmax(mx, sz[i]);
		}
	}
	chkmax(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

void build_centr(int v, int p, int size, int len) {
	dfs_centr(v, -1, size);
	v = centr;
	used[v] = true;
	par[v] = p;
	h_centr[v] = len++;
	for (auto i : g[v]) {
		if (!used[i]) {
			int fsz = sz[i];
			if (sz[i] > sz[v]) {
				fsz = size - sz[v];
			}
			build_centr(i, v, fsz, len);
		}
	}
}

void build() {
	build_coords();
	dfs_lca(0, 0, 0);
	build_centr(0, -1, n, 0);
}

int ans;

void run() {
	build();
}

void write() {
	cout << ans << endl;
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