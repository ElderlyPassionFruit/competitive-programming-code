#pragma GCC optimize("unroll-loops")
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

struct event{
	segment a;
	int len;
	event() {}
	event(segment x, int y) {
		a = x, len = y;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.len, a.a) < tie(b.len, b.a);
}

segment merge(const segment & a, const segment & b) {
	segment ans;
	ans.l = max(a.l, b.l);
	ans.r = min(a.r, b.r);
	return ans;
}

bool check(const segment & a) {
	return a.l > a.r;
}

const int MAXN = 1e6 + 10;
int n, k;
vector<int> g[MAXN];
vector<segment> have[MAXN];

void read() {
	//cin >> n >> k;
	scanf("%d%d",&n,&k);
	for (int i = 0; i < n; i++) {
		have[i].resize(k);
		for (int j = 0; j < k; j++){
			scanf("%d",&have[i][j].l);
			//cin >> have[i][j].l;
		}
		for (int j = 0; j < k; j++){
			scanf("%d",&have[i][j].r);
			//cin >> have[i][j].r;
		}
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d%d",&u,&v);
		//cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

bool used[MAXN];
int sz[MAXN];
int centr;

void dfs_centr(int v, int p, int size) {
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
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

const int INF = 1e9;

struct segment_tree{
	vector<multiset<int> > have_l, have_r;
	vector<int> tree_l, tree_r;
	vector<int> pos;
	int n;
	segment_tree() {}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}

	segment_tree(int sz) {
		n = sz;
		have_l.resize(n);
		have_r.resize(n);
		tree_l.resize(n * 4, INF);
		tree_r.resize(n * 4, INF);
		pos.resize(n);
		build(1, 0, n);
	}

	void upd_l(int p, int val) {
		int v = pos[p];
		tree_l[v] = val;
		v /= 2;
		while (v) {
			tree_l[v] = min(tree_l[v * 2], tree_l[v * 2 + 1]);
			v /= 2;
		}
 	}

	void upd_r(int p, int val) {
		int v = pos[p];
		tree_r[v] = val;
		v /= 2;
		while (v) {
			tree_r[v] = min(tree_r[v * 2], tree_r[v * 2 + 1]);
			v /= 2;
		}
	}

	void add(event a) {
		have_l[a.a.l].insert(a.len);
		upd_l(a.a.l, *have_l[a.a.l].begin());
		have_r[a.a.r].insert(a.len);
		upd_r(a.a.r, *have_r[a.a.r].begin());
	}

	void del(event a) {
		have_l[a.a.l].erase(have_l[a.a.l].find(a.len));
		if (!have_l[a.a.l].empty()) {
			upd_l(a.a.l, *have_l[a.a.l].begin());
		}
		else {
			upd_l(a.a.l, INF);
		}
		have_r[a.a.r].erase(have_r[a.a.r].find(a.len));
		if (!have_r[a.a.r].empty()) {
			upd_r(a.a.r, *have_r[a.a.r].begin());
		}
		else {
			upd_r(a.a.r, INF);
		}
	}

	int get_l(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return INF;
		if (tl >= l && tr <= r) return tree_l[v];
		int tm = (tl + tr) / 2;
		return min(get_l(v * 2, tl, tm, l, r), get_l(v * 2 + 1, tm, tr, l, r));
	}
	
	int get_r(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return INF;
		if (tl >= l && tr <= r) return tree_r[v];
		int tm = (tl + tr) / 2;
		return min(get_r(v * 2, tl, tm, l, r), get_r(v * 2 + 1, tm, tr, l, r));
	}

	int get_l(int pos) {
		return get_l(1, 0, n, pos, n);
	}

	int get_r(int pos) {
		return get_r(1, 0, n, 0, pos + 1);
	}

	int get(event a) {
		return a.len + min(get_l(a.a.r + 1), get_r(a.a.l - 1));
	}
};

//multiset<event> path;
segment_tree path;
//event INF = {{1, 0}, 1e9};
int ans;

void dfs_path(int v, int p, segment now, bool flag, int ind, int len) {
	now = merge(now, have[v][ind]);
	if (flag) {
		//path.insert({now, len});
		path.add({now, len});
	}
	else {
		//path.erase(path.find({now, len}));
		path.del({now, len});
	}
	if (check(now)) {
		chkmin(ans, len);
	}
	len++;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_path(i, v, now, flag, ind, len);
		}
	}
}

void add(int v, int ind, segment start) {
	dfs_path(v, -1, start, 1, ind, 1);
}

void del(int v, int ind, segment start) {
	dfs_path(v, -1, start, 0, ind, 1);
}

void dfs_calc(int v, int p, segment now, int ind, int len) {
	chkmin(ans, path.get({have[v][ind], len}));
	len++;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_calc(i, v, now, ind, len);
		}
	}	
}

void relax(int v, int ind, segment start) {
	dfs_calc(v, -1, start, ind, 1);
}

void rebuild() {

}

void solve(int v, int size, int ind, int len) {
	assert(len < 20);
	dfs_centr(v, -1, size);
	
	v = centr;
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i]) {
			add(i, ind, have[v][ind]);
		}
	}
	
	rebuild();
	for (auto i : g[v]) {
		if (!used[i]) {
			relax(i, ind, have[v][ind]);
		}
	}
	
	for (auto i : g[v]) {
		if (!used[i]) {
			del(i, ind, have[v][ind]);
		}
	}

	for (auto i : g[v]) {
		if (!used[i]) {
			int fsz = sz[i];
			if (sz[i] > sz[v])
				fsz = size - sz[v];
			solve(i, fsz, ind, len + 1);
		}
	}
}

void solve(int ind) {
	for (int i = 0; i < n; i++)
		used[i] = false;
	solve(0, n, ind, 0);
}

void build() {
	int sz = 0;
	for (int ind = 0; ind < k; ind++) {
		vector<int> coord;
		for (int i = 0; i < n; i++) {
			coord.push_back(have[i][ind].l);
			coord.push_back(have[i][ind].r);
			if (have[i][ind].l > have[i][ind].r) 
				swap(have[i][ind].l, have[i][ind].r);
		}
		sort(all(coord));
		coord.resize(unique(all(coord)) - coord.begin());
		for (int i = 0; i < n; i++) {
			have[i][ind].l = lower_bound(all(coord), have[i][ind].l) - coord.begin();
			have[i][ind].r = lower_bound(all(coord), have[i][ind].r) - coord.begin();
		}
		chkmax(sz, coord.size());
	}
	//cout << "sz = " << sz << endl;
	path = segment_tree(sz);
}

void wr() {
	cout << "have = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << endl;
		for (int j = 0; j < k; j++) {
			cout << have[i][j].l << " " << have[i][j].r << endl;
		}
		cout << endl;
	}

	cout << "g = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i =  " << i << endl;
		cout << "ed = ";
		for (auto j : g[i]) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void run() {
	build();
	ans = n + 1;
	for (int i = 0; i < k; i++) {
		solve(i);
	}
	if (ans == n + 1)
		ans = -1;
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