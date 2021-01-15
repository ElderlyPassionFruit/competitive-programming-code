#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment_tree{
	vector<int> tree;
	int n;

	segment_tree() {
		tree = {};
		n = 0;
	}

	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = a[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
	}

    explicit segment_tree(vector<int> a) {
		n = a.size();
		tree.assign(n * 4, 0);
		build(1, 0, n, a);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return 0;
		if (tl >= l && tr <= r)
			return tree[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l)
			return;
		if (tl >= l && tr <= r) {
			tree[v] = val;
			return;
		}
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
	}

	void upd(int pos, int h) {
		upd(1, 0, n, pos, pos + 1, h);
	}
};

const int MAXN = 5e4 + 10, MAXLOG = 20;
int n;
vector<int> g[MAXN];
int a[MAXN];

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN];
int timer = 0;

int sz[MAXN];

vector<vector<int> > path;
pair <int, int> ind[MAXN];

vector<segment_tree> tree;

void dfs_lca(int v, int p, int len) {
	h[v] = len++;
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	}
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
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	}
	return dp[v][0];
}

int dist(int u, int v) {
	return h[u] + h[v] - 2 * h[lca(u, v)];
}

void dfs_sz(int v, int p) {
	sz[v] = 1;
	for (auto i : g[v]) {
		if (i != p) {
			dfs_sz(i, v);
			sz[v] += sz[i];
		}
	}
}

void dfs_hld(int v, int p, int ind1, int ind2) {
	path[ind1].push_back(v);
	ind[v] = {ind1, ind2};
	for (auto i : g[v]) {
		if (i != p) {
			if (sz[i] > sz[v] / 2) {
				dfs_hld(i, v, ind1, ind2 + 1);
			}
			else {
				path.push_back({});
				dfs_hld(i, v, path.size() - 1, 0);
			}
		}
	}
}

int get_max(int l, int v) {
	int ans = 0;
	int cnt = dist(l, v) + 1;
	while (cnt) {
		int i = ind[v].first;
		int j = ind[v].second;
		int help = min(cnt, j + 1);
		chkmax(ans, tree[i].get(j + 1 - help, j));
		v = dp[path[i][0]][0];
		cnt -= help;
	}
	return ans;
}

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

void make() {
	dfs_lca(0, 0, 0);
	dfs_sz(0, 0);
	path.push_back({});
	dfs_hld(0, 0, 0, 0);
	for (int i = 0; i < path.size(); i++) {
		vector<int> help;
		for (auto j : path[i])
			help.push_back(a[j]);
		tree.push_back(segment_tree(help));
	}
}

void upd(int pos, int val) {
	tree[ind[pos].first].upd(ind[pos].second, val);
}

int solve(int u, int v) {
	int l = lca(u, v);
	return max(get_max(l, u), get_max(l, v));
}

vector<int> ans;

void run() {
	make();
	int k;
	cin >> k;

	for (int i = 0; i < k; i++) {
		char type;
		cin >> type;
		if (type == '?') {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			ans.push_back(solve(u, v));
		}
		if (type == '!') {
			int pos, val;
			cin >> pos >> val;
			pos--;
			upd(pos, val);
		} 
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
}

signed main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}