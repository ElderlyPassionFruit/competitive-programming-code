#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
vector<int> gr[MAXN], g[MAXN];
int n, d;

void read() {
	cin >> n >> d;
	if (d % 2 == 1) {
		cout << 0 << endl;
		exit(0);
	}
	d /= 2;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		gr[u].push_back(v);
		gr[v].push_back(u);
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

ll ans;

int cnt[MAXN];
int h[MAXN];
int fans[MAXN];

void dfs_precalc(int v, int p, int len, int type) {
	h[v] = len;
	cnt[h[v]] += type;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) continue;
		dfs_precalc(i, v, len + 1, type);
	}
}

void dfs_calc(int v, int p, int len) {
	h[v] = len;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) continue;
		dfs_calc(i, v, len + 1);
	}
	int other = d - len;
	if (other < 0) return;
	fans[v] += cnt[other];
}

void solve(int v, int size) {
	dfs_centroid(v, -1, size);
	v = centr;
	used[v] = true;
	cnt[0]++;

	for (auto i : g[v]) {
		if (used[i]) continue;
		dfs_precalc(i, v, 1, 1);
	}

	for (auto i : g[v]) {
		if (used[i]) continue;
		dfs_precalc(i, v, 1, -1);
		dfs_calc(i, v, 1);
		dfs_precalc(i, v, 1, 1);
	}

	fans[v] += cnt[d];

	dfs_precalc(v, -1, 0, -1);
	for (auto i : g[v]) {
		if (used[i]) continue;
		int fsz = sz[i];
		if (fsz > sz[v]) {
			fsz = size - sz[v];
		}
		solve(i, fsz);
	}
}

vector<int> have[MAXN];
int tin[MAXN], tout[MAXN], timer = 0;
int par[MAXN];

void dfs_tin(int v, int p, int len) {
	par[v] = p;
	tin[v] = timer++;
	h[v] = len;
	have[len].push_back(tin[v]);
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_tin(i, v, len + 1);
	}
	tout[v] = timer;
}

void dfs_renum(int v, int p) {
	tin[v] = timer++;
	for (auto i : gr[v]) {
		if (i == p) continue;
		dfs_renum(i, v);
	}
}

void renum() {
	dfs_renum(0, 0);
	for (int i = 0; i < n; i++) {
		for (auto j : gr[i]) {
			g[tin[i]].push_back(tin[j]);
		}
	}
}

void build() {
	renum();
	solve(0, n);
	dfs_tin(0, 0, 0);
}

void calc() {
	for (int v = 0; v < n; v++) {
		int sum = 0;
		ll mul = 0;
		for (auto i : g[v]) {
			int add = 0;
			if (i == par[v]) {
				add = fans[v];
				if (h[v] + d < n) {
					add -= lower_bound(all(have[h[v] + d]), tout[v]) - lower_bound(all(have[h[v] + d]), tin[v]);
				}
			} else {
				if (h[v] + d < n) {
					add = lower_bound(all(have[h[v] + d]), tout[i]) - lower_bound(all(have[h[v] + d]), tin[i]);
				}
			}
			ans += (ll)add * mul;
			mul += (ll)add * sum;
			sum += add;
		}
	}
}

void run() {
	build();
	calc();
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
