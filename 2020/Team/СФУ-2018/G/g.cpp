#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 2e5 + 10, MAXLOG = 20;
vector<int> g[MAXN];
int n, q, D;

int dp[MAXN][MAXLOG];
int tin[MAXN], tout[MAXN], timer = 0;

void dfs_lca(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_lca(i, v);
	}
	tout[v] = timer++;
}

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

pair<int, int> lca(int v, int u) {
	for (int i = MAXLOG - 1; i >= 0; i--) 
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	for (int i = MAXLOG - 1; i >= 0; i--) 
		if (!is_upper(dp[u][i], v))
			u = dp[u][i];
	return {v, u};
}

vector<int> have[MAXN];
int h[MAXN];

void dfs_h(int v, int p) {
	have[h[v]].push_back(tin[v]);
	for (auto i : g[v]) {
		if (i == p) continue;
		h[i] = h[v] + 1;
		dfs_h(i, v);
	}
}

int calc(int v, int len) {
	if (h[v] + len >= MAXN) return 0;
	return lower_bound(all(have[h[v] + len]), tout[v]) - lower_bound(all(have[h[v] + len]), tin[v]);
}

int cnt_subtree[MAXN];

void dfs_subtree(int v, int p) {
	cnt_subtree[v] = 1;
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_subtree(i, v);
		cnt_subtree[v] += cnt_subtree[i];
	}	
	cnt_subtree[v] -= calc(v, D + 1);
}

int cnt_all[MAXN];

void dfs_all(int v, int p, int len) {
	if (len == -1) return;
	cnt_all[v]++;
	len--;
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_all(i, v, len);
	}
}

int pref[MAXN];

void dfs_pref(int v, int p) {
	if (v == 0) {
		pref[v] = cnt_all[v];
	} else {
		pref[v] = pref[p] + calc(v, D);
	}
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_pref(i, v);
	}
}

int sz[MAXN];
bool used[MAXN];
int centr;

inline void chkmax(int & x, int y) {
	if (x < y) x = y;
}

void dfs_centr(int v, int p, int size) {
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) continue;
		dfs_centr(i, v, size);
		chkmax(mx, sz[i]);
		sz[v] += sz[i];
	}
	chkmax(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

int tree[MAXN];

void upd(int pos, int val) {
	for (; pos < n; pos |= pos + 1)
		tree[pos] += val;
}

int get(int r) {
	int ans = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1)
		ans += tree[r];
	return ans;
}

void dfs_precalc(int v, int p, int len, int flag) {
	if (len == -1) return;
	upd(D - len, flag);
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) continue;
		dfs_precalc(i, v, len - 1, flag);
	}
}

void dfs_calc(int v, int p, int len) {
	if (len == -1) return;
	cnt_all[v] += get(len);
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) continue;
		dfs_calc(i, v, len - 1);
	}
}

void find_centr(int v, int size) {
	dfs_centr(v, -1, size);
	v = centr;
	used[v] = true;

	dfs_precalc(v, -1, D, 1);
	cnt_all[v] += get(D);
	for (auto i : g[v]) {
		if (used[i]) continue;
		dfs_precalc(i, v, D - 1, -1);
		dfs_calc(i, v, D - 1);
		dfs_precalc(i, v, D - 1, 1);
	}
	dfs_precalc(v, -1, D, -1);

	for (auto i : g[v]) {
		if (used[i]) continue;
		int fsz = sz[i];
		if (fsz > sz[v]) {
			fsz = size - sz[v];
		}
		find_centr(i, fsz);
	}
}

void build() {
	dfs_lca(0, 0);
	dfs_h(0, 0);
	dfs_subtree(0, 0);
	find_centr(0, n);
	dfs_pref(0, 0);
}

int solve(int u, int v) {
	if (u == v) return cnt_all[u];
	if (is_upper(v, u) || is_upper(u, v)) {
		if (is_upper(u, v)) swap(u, v);
		int ans = 0;
		auto l = lca(v, u);
		ans += pref[u] - (pref[v] - (cnt_subtree[l.second] - calc(l.second, D)));
		ans += cnt_all[v] - (cnt_subtree[l.second] - calc(l.second, D));
		return ans;
	}
	int ans = 0;
	auto l = lca(u, v);
	int LCA = dp[l.first][0];
	ans += pref[u] - (pref[LCA] - (cnt_subtree[l.first] - calc(l.first, D)));
	ans += pref[v] - (pref[LCA] - (cnt_subtree[l.second] - calc(l.second, D)));
	ans += cnt_all[LCA] - (cnt_subtree[l.first] - calc(l.first, D)) - (cnt_subtree[l.second] - calc(l.second, D));
	return ans;
}

mt19937 rnd(time(0));

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cin >> q >> D;
	build();
	while (q--) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		cout << solve(u, v) << "\n";
	}
	return 0;
}