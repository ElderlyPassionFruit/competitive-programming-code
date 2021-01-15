#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = -1e9 - 10;

int merge(int a, int b) {
	return max(a, b);
}

struct segment_tree{
	vector<int> tree;
	vector<int> coord;
	int n;
	segment_tree() {
		n = 0;
		tree = {};
		coord = {};
	}

	segment_tree(int sz) {
		n = sz;
		tree.resize(4 * n, 0);
		coord.resize(n);
	}

	void build(int v, int tl, int tr, vector<int> & a) {
		if (tl == tr - 1) {
			tree[v] = a[tl];
			coord[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(vector<int> a) {
		n = a.size();
		tree.assign(n * 4, INF);
		coord.resize(n);
		build(1, 0, n, a);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return INF;
		if (tl >= l && tr <= r)
			return tree[v];
		int tm = (tl + tr) / 2;
		return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}

	void upd(int pos, int val) {
		int v = coord[pos];
		tree[v] = val;
		v /= 2;
		while (v) {
			tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}
};

const int MAXN = 1e5 + 10, MAXLOG = 20;

int n;
vector<int> g[MAXN];
int w[MAXN];

int sz[MAXN];

vector<vector<int> > path;
int id[MAXN][2];

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], timer = 0;

vector<segment_tree> tree;
vector<int> ans;

void read() {
	cin >> n;
	//for (int i = 0; i < n; i++)
	//	cin >> w[i];
	for (int i = 0; i < n; i++)
		w[i] = 0;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
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
	id[v][0] = ind1;
	id[v][1] = ind2;
	path[ind1].push_back(v);
	for (auto i : g[v]) {
		if (i != p) {
			if (sz[i] * 2 >= sz[v]) {
				dfs_hld(i, v, ind1, ind2 + 1);
			}
			else {
				path.push_back({});
				dfs_hld(i, v, path.size() - 1, 0);
			}
		}
	}
}

void dfs_lca(int v, int p, int len) {
	tin[v] = timer++;
	h[v] = len++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v])
		if (i != p)
			dfs_lca(i, v, len);
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

void build() {
	dfs_sz(0, 0);
	path.push_back({});
	dfs_hld(0, 0, 0, 0);
	for (auto i : path) {
		vector<int> help;
		for (auto j : i)
			help.push_back(w[j]);
		tree.push_back(segment_tree(help));
	}
	dfs_lca(0, 0, 0);
}

void upd(int pos, int val) {
	w[pos] += val;
	tree[id[pos][0]].upd(id[pos][1], w[pos]);
}

int get_pred(int v) {
	return dp[v][0];
}

int get_ans(int l, int u) {
	int ans = INF;
	int cnt = h[u] - h[l] + 1;
	while (cnt) {
		int id1 = id[u][0];
		int id2 = id[u][1];
		int up = min(cnt, id2 + 1);
		ans = merge(ans, tree[id1].get(id2 - up + 1, id2));
		u = get_pred(path[id1][id2 - up + 1]);
		cnt -= up;
	}
	return ans;
}

int get(int u, int v) {
	int l = lca(u, v);
	return merge(get_ans(l, u), get_ans(l, v));
}

void run() {
	build();	
	int q;
	cin >> q;
	for (int test = 0; test < q; test++) {
		char type;
		cin >> type;
		if (type == 'I') {
			int pos, val;
			cin >> pos >> val;
			pos--;
			upd(pos, val);
		}
		else if (type == 'G') {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			int fans = get(u, v);
			ans.push_back(fans);
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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