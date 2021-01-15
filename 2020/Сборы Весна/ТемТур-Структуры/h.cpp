#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

//#define int ll

struct segment{
	int l, r, v;
	segment() {}
	segment(int _l, int _r, int _v) {
		l = _l, r = _r, v = _v;
	}
};

struct query{
	int v, val, pos, pos_ans;
	query() {}
	query(int _v, int _val, int _pos, int _pos_ans) {
		v = _v, val = _val, pos = _pos, pos_ans = _pos_ans;
	}
};

const int MAXN = 3e5 + 10;

namespace graph{
	int n;
	vector<int> g[MAXN];
	void init(int _n) {
		n = _n;
		fill(g, g + MAXN, vector<int> ());
	}

	const int MAXLOG = 19;
	int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], timer = 0;

	void dfs(int v, int p, int len) {
		tin[v] = timer++;
		h[v] = len++;
		dp[v][0] = p;
		for (int i = 1; i < MAXLOG; i++) {
			dp[v][i] = dp[dp[v][i - 1]][i - 1];
		}
		for (auto to : g[v]) {
			if (to == p) continue;
			dfs(to, v, len);
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

	int dist(int v, int u) {
		return h[v] + h[u] - 2 * h[lca(v, u)];
	}

	pair<int, int> best[MAXN];

	void dfs_down(int v, int p) {
		best[v] = {v, -1};
		for (auto to : g[v]) {
			if (to == p) continue;
			dfs_down(to, v);
			if (best[v].second == -1 || dist(best[v].second, v) < dist(best[to].first, v))
				best[v].second = best[to].first;
			if (dist(best[v].first, v) < dist(best[v].second, v))
				swap(best[v].first, best[v].second);
		}
	}

	void dfs_up(int v, int p) {
		if (p != -1) {
			int upd_v = -1;
			if (!is_upper(v, best[p].first)) {
				upd_v = best[p].first;
			} else {
				upd_v = best[p].second;
			}
			assert(upd_v != -1);
			if (best[v].second == -1 || dist(best[v].second, v) < dist(upd_v, v))
				best[v].second = upd_v; 
			if (dist(best[v].first, v) < dist(best[v].second, v))
				swap(best[v].first, best[v].second);
		}
		for (auto to : g[v]) {
			if (to == p) continue;
			dfs_up(to, v);
		}
	}

	void build() {
		dfs(0, 0, 0);
		dfs_down(0, 0);
		dfs_up(0, -1);
	}

	bool cmp(int a, int b) {
		return tin[a] < tin[b];
	}
}

namespace segment_tree{
	vector<int> tree[MAXN * 4];
	vector<query> q[MAXN * 4];
	int pos[MAXN];
	int n;

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}

	void init(int _n) {
		n = _n;
		fill(tree, tree + MAXN * 4, vector<int> ());
		fill(q, q + MAXN * 4, vector<query> ());
		fill(pos, pos + MAXN, 0);
		build(1, 0, n);
	}

	void add_query(query x) {
		int v = pos[x.pos];
		while (v) {
			q[v].push_back(x);
			v /= 2;
		}
	}

	void add(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l) return;
		if (tl >= l && tr <= r) {
			tree[v].push_back(val);
			return;
		}
		int tm = (tl + tr) / 2;
		add(v * 2, tl, tm, l, r, val);
		add(v * 2 + 1, tm, tr, l, r, val);
	}

	void add_segment(segment x) {
		add(1, 0, n, x.l, x.r + 1, x.v);
	}
}

int a[MAXN];
int n, q;
int open[MAXN];

vector<segment> have;
vector<query> need;

void read() {
	cin >> n >> q;
	graph::init(n);
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		graph::g[p].push_back(i);
		graph::g[i].push_back(p);
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		open[i] = 0;
	}
	for (int i = 0; i < q; i++) {
		char type;
		cin >> type;
		if (type == '?') {
			int v, T;
			cin >> v >> T;
			v--;
			need.push_back({v, T, i, (int)need.size()});
		} else if (type == '+') {
			int v;
			cin >> v;
			v--;
			open[v] = i;
		} else {
			int v;
			cin >> v;
			v--;
			have.push_back({open[v], i, v});
			open[v] = -1;
		}
	}
	for (int i = 0; i < n; i++) {
		if (open[i] != -1) {
			have.push_back({open[i], q, i});
		}
	}
}

vector<ll> ans;

void build() {
	ans.assign(need.size(), 0);
	segment_tree::init(q + 1);
	for (auto i : need) {
		segment_tree::add_query(i);
	}
	for (auto i : have) {
		segment_tree::add_segment(i);
	}
	graph::build();
}

vector<int> make_vert(vector<int> & v, vector<query> & q) {
	vector<int> have;
	for (auto i : v) have.push_back(i);
	for (auto i : q) have.push_back(i.v);
	sort(all(have), graph::cmp);
	have.resize(unique(all(have)) - have.begin());
	int sz = have.size();
	for (int i = 1; i < sz; i++) {
		have.push_back(graph::lca(have[i - 1], have[i]));
	}
	sort(all(have), graph::cmp);
	have.resize(unique(all(have)) - have.begin());
	return have;
}

const int INF = -1e9 - 228 - 1337;

struct line{
	int k, b;
	line() {
		k = 0, b = INF;
	}
	line(ll _k, ll _b) {
		k = _k, b = _b;
	}
};

ll eval(line l, ll x) {
	return (ll)l.k * x + l.b;
}

struct node{
	line x;
	int l, r;
	node() {
		x = {};
		l = -1;
		r = -1;
	}
	node(line _x) {
		x = _x;
		l = -1;
		r = -1;
	}
};

const int MAXMEM = 3e5 + 10;
node tree[MAXMEM];
int topQ;
const int L = 0, R = 1e9 + 10;
const int MAXMEM2 = 1e7 + 10;
pair<int, node> fupd[MAXMEM2];
int topUpd;
int cnt = 0;

int upd(line x, int root, int tl, int tr) {
	if (root == -1) {
		tree[topQ] = node(x);
		fupd[topUpd++] = {topQ, line()};
		cnt++;	
		topQ++;
		return topQ - 1;
	}
	int tm = (tl + tr) / 2;
	bool left = eval(x, tl) > eval(tree[root].x, tl);
	bool mid = eval(x, tm) > eval(tree[root].x, tm);
	if (mid) {
		fupd[topUpd++] = {root, tree[root]};
		cnt++;	
		swap(tree[root].x, x);
	}
	if (tl == tr - 1) return root;
	if (left != mid) {
		tree[root].l = upd(x, tree[root].l, tl, tm);
	} else {
		tree[root].r = upd(x, tree[root].r, tm, tr);
	}
	return root;
}

void upd(int & root, line x) {
	root = upd(x, root, L, R);
}

ll get(int x, int root, int tl, int tr) {
	if (tl >= x + 1 || tr <= x) return INF;
	if (root == -1) return INF;
	if (tl == tr - 1) return eval(tree[root].x, x);
	int tm = (tl + tr) / 2;
	ll ans = eval(tree[root].x, x);
	chkmax(ans, get(x, tree[root].l, tl, tm));
	chkmax(ans, get(x, tree[root].r, tm, tr));
	return ans;
}

ll get(int root, int x) {
	return get(x, root, L, R);
}

void undo(int cnt) {
	//assert((int)fupd.size() >= cnt);
	for (int i = 0; i < cnt; i++) {
		int root = fupd[topUpd - 1].first;
		node l = fupd[topUpd - 1].second;
		tree[root] = l;
		topUpd--;
		//fupd.pop_back();
	}
}
/*struct cht{
	vector<line> lines;
	cht() {}
	void upd(line l) {
		lines.push_back(l);
	}
	void del() {
		assert(!lines.empty());
		lines.pop_back();
	}
	ll get(ll x) {
		ll ans = INF;
		for (auto i : lines)
			chkmax(ans, eval(i, x));
		return ans;
	}
};*/

void dfs(int v, vector<vector<int>> & g, vector<int> & have, vector<bool> & have_port, vector<vector<query>> & have_query, int tree) {
	int real_v = have[v];
	//int last_tree;// = clone(tree);
	//tree = clone(tree);
	int need_undo = 0;
	if (have_port[v]) {
		need_undo = cnt;
		upd(tree, line(graph::dist(real_v, graph::best[real_v].first), a[real_v]));
		need_undo = cnt - need_undo;
		//cerr << "v = " << v << " dist1 = " << graph::dist(real_v, graph::best[real_v].first) << " " << graph::dist(real_v, graph::best[real_v].second) << endl;
	}
	for (auto i : have_query[v]) {
		chkmax(ans[i.pos_ans], get(tree, i.val));
	}
	int x = -1;
	for (auto i : g[v]) {
		//cerr << have[i] << " " << graph::best[real_v].first << endl;
		if (have_port[v] && !graph::is_upper(graph::lca(have[i], graph::best[real_v].first), real_v)) {
			x = i;
			//cerr << have[i] << " " << have[v]<< endl;
			//cerr << "puhh" << endl;
			//upd(tree, line(graph::dist(real_v, graph::best[real_v].second), a[real_v]));
	
			//dfs(i, g, have, have_port, have_query, tree);
		} else {
			dfs(i, g, have, have_port, have_query, tree);
		}
	}	
	undo(need_undo);
	if (x != -1) {
		need_undo = cnt;
		upd(tree, line(graph::dist(real_v, graph::best[real_v].second), a[real_v]));
		need_undo = cnt - need_undo;
		dfs(x, g, have, have_port, have_query, tree);
		undo(need_undo);
	}
}

void solve(vector<int> & v, vector<query> & q) {
	vector<int> have = make_vert(v, q);
	for (auto &i : v)
		i = lower_bound(all(have), i, graph::cmp) - have.begin();
	for (auto &i : q)
		i.v = lower_bound(all(have), i.v, graph::cmp) - have.begin();

	vector<vector<query>> have_query(have.size());
	for (auto i : q)
		have_query[i.v].push_back(i);
	
	vector<bool> have_port(have.size(), false);
	for (auto i : v){
		have_port[i] = true;
	}

	vector<vector<int>> g(have.size());
	vector<int> st;
	for (int i = 0; i < (int)have.size(); i++) {
		while (!st.empty() && !graph::is_upper(have[st.back()], have[i]))
			st.pop_back();
		if (!st.empty()) {
			g[st.back()].push_back(i);
		}
		st.push_back(i);
	}

	int tree = -1;
	topQ = 0;
	topUpd = 0;
	dfs(0, g, have, have_port, have_query, tree);
}

void solve() {
	for (int i = 0; i <= q * 4; i++) {
		if (segment_tree::tree[i].empty()) continue;
		if (segment_tree::q[i].empty()) continue;
		solve(segment_tree::tree[i], segment_tree::q[i]);
		//cerr << "puhh" << endl;
	}
}

void run() {
	build();
	solve();
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

/*
3 1
1 2 
1 1 1 
? 3 1

5 8
1 2 2 1 
1 1 1 1 1 
- 4
- 5
- 2
? 4 1
- 3
? 4 1
? 4 1
+ 3

4 9
1 2 2 
3 4 5 1 
- 2
- 3
+ 3
- 4
+ 2
+ 4
- 4
? 4 4
- 2


4 4
1 2 2 
1 2 1 2 
- 3
- 4
- 2
? 4 1

*/