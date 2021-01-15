#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9 + 10;
struct node{
	int val, mod;
	node() {
		val = 0, mod = INF;
	}
	node(int a, int b) {
		val = a, mod = b;
	}
};

struct segment_tree{
	vector<node> tree;
	int n;
	segment_tree() {
		n = 0;
		tree = {};
	}

	segment_tree(int sz) {
		n = sz;
		tree.resize(4 * n);
	}

	void push(int v) {
		if (tree[v].mod == INF) return;
		tree[v * 2].mod = tree[v].mod;
		tree[v * 2 + 1].mod = tree[v].mod;
		tree[v].val = tree[v].mod;
		tree[v].mod = INF;
	}

	int get(node a) {
		return (a.mod == INF ? a.val : a.mod);	
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l)  {
			return;
		}
		if (tl >= l && tr <= r) {
			tree[v].mod = val;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
	}

	void upd(int l, int r, int val) {
		upd(1, 0, n, l, r + 1, val);
	}

	int get(int v, int tl, int tr, int pos) {
		if (tl >= pos + 1 || tr <= pos) return INF;
		if (tl == tr - 1) return get(tree[v]);
		push(v);
		int tm = (tl + tr) / 2;
		return min(get(v * 2, tl, tm, pos), get(v * 2 + 1, tm, tr, pos));
	}

	int get(int pos) {
		return get(1, 0, n, pos);
	}
};

struct event{
	int type, x, y1, y2, ind, color, y;
	event() {}
	event(int a, int b, int c, int d, int e) {
		type = a, x = b, y1 = c, y2 = d, ind = e;
	}
	event(int a, int b, int c, int d) {
		type = a, x = b, y = c, color = d;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.type) < tie(b.x, b.type);
}

int n, m;
vector<event> a;
segment_tree tree;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		a.push_back({1, x1, y1, y2, i + 1});
		a.push_back({3, x2, y1, y2, i + 1});
	}
	for (int i = 0; i < m; i++) {
		int x, y, k;
		cin >> x >> y >> k;	 
		a.push_back({2, x, y, k});
	}
} 

void make() {
	vector<int> have_x;
	vector<int> have_y;
	vector<int> color;

	for (auto i : a) {
		have_x.push_back(i.x); 
		if (i.type == 1 || i.type == 3) {
			have_y.push_back(i.y1);
			have_y.push_back(i.y2);
		}
		else {
			have_y.push_back(i.y);
			color.push_back(i.color);
		}
	}

	sort(have_x.begin(), have_x.end());
	sort(have_y.begin(), have_y.end());
	sort(color.begin(), color.end());
	have_x.erase(unique(have_x.begin(), have_x.end()), have_x.end());
	have_y.erase(unique(have_y.begin(), have_y.end()), have_y.end());
	color.erase(unique(color.begin(), color.end()), color.end());

	tree = segment_tree(have_y.size());
	tree.upd(0, have_y.size(), -1);

	for (auto &i : a) {
		i.x = lower_bound(have_x.begin(), have_x.end(), i.x) - have_x.begin();
		if (i.type == 1 || i.type == 3) {
			i.y1 = lower_bound(have_y.begin(), have_y.end(), i.y1) - have_y.begin();
			i.y2 = lower_bound(have_y.begin(), have_y.end(), i.y2) - have_y.begin();
		}
		else {
			i.y = lower_bound(have_y.begin(), have_y.end(), i.y) - have_y.begin();
			i.color = lower_bound(color.begin(), color.end(), i.color) - color.begin();
		}
	}

	sort(a.begin(), a.end());
}

const int MAXN = 3e5 + 10;
int par[MAXN];
vector<int> root;
vector<int> g[MAXN];
vector<int> colors[MAXN];

void build_graph() {
	for (auto i : a) {
		if (i.type == 1) {
			int v = tree.get(i.y1);
			par[i.ind] = v;
			tree.upd(i.y1, i.y2, i.ind);
		}
		else if (i.type == 3) {
			tree.upd(i.y1, i.y2, par[i.ind]);
		}
		else {
			int v = tree.get(i.y);
			if (v == -1) continue;
			colors[v].push_back(i.color);
		}
	}

	for (int i = 1; i <= n; i++) {
		if (par[i] == -1) {
			g[0].push_back(i);
		}
		else {
			g[par[i]].push_back(i);
		}
	}
}

const int MAXLOG = 20;
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0;

void dfs_lca(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];

	for (auto i : g[v])
		dfs_lca(i, v);
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

void build_lca() {
	dfs_lca(0, 0);
}

int last[MAXN];
int ans[MAXN];

void dfs_colors(int v) {
	for (auto i : colors[v]) {
		if (last[i] != -1) 
			ans[lca(last[i], v)]--;
		last[i] = v;
	}

	ans[v] += colors[v].size();
	
	for (auto i : g[v])
		dfs_colors(i);
}

void build_colors() {
	for (int i = 0; i <= m; i++)
		last[i] = -1;
	dfs_colors(0);
}

void dfs_ans(int v) {
	for (auto i : g[v]) {
		dfs_ans(i);
		ans[v] += ans[i];
	}
}

void solve() {
	dfs_ans(0);
}

void run() {
	make();
	build_graph();
	build_lca();
	build_colors();
	solve();
}

void write() {
	for (int i = 1; i <= n; i++)
		cout << ans[i] << "\n";
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