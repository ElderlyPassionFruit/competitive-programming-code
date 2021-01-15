#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n, q;
vector<int> g[MAXN];	

int sz[MAXN], par[MAXN], h[MAXN], tin[MAXN], tout[MAXN], timer = 0;
int nxt[MAXN];

void dfs_path(int v, int p) {
	sz[v] = 1;
	par[v] = p;
	nxt[v] = -1;
	for (auto to : g[v]) {
		if (to == p) continue;
		h[to] = h[v] + 1;
		dfs_path(to, v);
		sz[v] += sz[to];
		if (nxt[v] == -1 || sz[nxt[v]] < sz[to]) {
			nxt[v] = to;
		}
	}
}

int id[MAXN], par_path[MAXN], pos[MAXN], path_sz[MAXN];
int it = 0, cnt = 0;
int rtin[MAXN];

void dfs_build(int v, int p) {
	tin[v] = timer++;
	rtin[tin[v]] = v;
	id[v] = cnt;
	if (!path_sz[cnt]) {
		par_path[cnt] = v;
	}
	path_sz[cnt]++;
	pos[v] = it++;
	if (nxt[v] != -1) {
		dfs_build(nxt[v], v);
	}
	for (auto to : g[v]) {
		if (to == p) continue;
		if (to == nxt[v]) continue;
		cnt++;
		dfs_build(to, v);
	}
	tout[v] = timer - 1;
}

struct node{
	int valL, valR;
	bool flag;
	node() {
		valL = 0, valR = 0;
		flag = 0;
	}
	node(int _valL, int _valR) {
		valL = _valL;
		valR = _valR;
		flag = 0;
	}
	void change() {
		swap(valL, valR);
	}
};	

node merge(const node & a, const node & b) {
	return node(a.valL + b.valL, a.valR + b.valR);
}

node tree[MAXN * 4];
int sumL[MAXN], sumR[MAXN];

void build(int v, int tl, int tr) {
	if (tl == tr - 1) {
		tree[v] = node(sumL[rtin[tl]], sumR[rtin[tl]]);
		return; 
	}
	int tm = (tl + tr) / 2;
	build(v * 2, tl, tm);
	build(v * 2 + 1, tm, tr);
	tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

inline void push(int v) {
	if (!tree[v].flag) return;
	tree[v * 2].flag ^= 1;
	tree[v * 2 + 1].flag ^= 1;
	tree[v].flag = false;
}

inline node get_val(int v) {
	node ans = tree[v];
	if (ans.flag) ans.change();
	return ans;
}

void upd(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l) return;
	if (tl >= l && tr <= r) {
		tree[v].flag ^= 1;
		return;
	}
	int tm = (tl + tr) / 2;
	push(v);
	upd(v * 2, tl, tm, l, r);
	upd(v * 2 + 1, tm, tr, l, r);
	tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
}

void upd(int l, int r) {
	upd(1, 0, n, l, r + 1);
	/*for (int i = l; i <= r; i++) {
		swap(tree[i].ansL, tree[i].ansR);
		tree[i].ans = tree[i].ansL;
	}*/
} 

node get(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l) return node();
	if (tl >= l && tr <= r) return get_val(v);
	int tm = (tl + tr) / 2;
	push(v);
	node ans = merge(
		get(v * 2, tl, tm, l, r),
		get(v * 2 + 1, tm, tr, l, r)
	);
	

	tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
	return ans;
}

int get(int l, int r) {
	return get(1, 0, n, l, r + 1).valL;
	/*node ans = node();
	for (int i = l; i <= r; i++) {
		ans = merge(ans, tree[i]);
	}
	//cout << "l = " << l << " r = " << r << " ans.ans = " << ans.ans << endl;
	return ans.ans;*/
}

void init() {
	for (int v = 0; v < n; v++) {
		int sum = 0;
		for (int i = 0; i < (int)g[v].size(); i++) {
			sumL[g[v][i]] = sum + 1;
			sum += sz[g[v][i]];
		}
		sum = 0;
		for (int i = (int)g[v].size() - 1; i >= 0; i--) {
			sumR[g[v][i]] = sum + 1;
			sum += sz[g[v][i]];
		}
	}
	/*cout << "sumL = " << endl;
	for (int i = 0; i < n; i++) {
		cout << sumL[i] << " " << sumR[i] << endl;
	} */
	/*for (int v = 0; v < n; v++) {
		tree[tin[v]] = node(sumL[v], sumR[v]);
	}*/
	build(1, 0, n);
}

void build() {
	dfs_path(0, 0);
	dfs_build(0, 0);
	init();
}

int get_path(int a, int b) {
	int ans = 0;
	while (id[a] != id[b]) {
		if (h[par_path[id[a]]] < h[par_path[id[b]]]) {
			swap(a, b);
		}
		ans += get(pos[par_path[id[a]]], pos[a]);
		a = par[par_path[id[a]]];
	}
	if (h[a] > h[b]) {
		swap(a, b);
	}
	ans += get(pos[a], pos[b]);
	return ans;
}

void upd_subtree(int v) {
	//cout << "L, R = " << endl;
	//cout << tin[v] + 1 << " " << tout[v] << endl;
	upd(tin[v] + 1, tout[v]);
}

int now;

int solve() {
	return get_path(now, 0);
}

void print() {
	cout << "tree = " << endl;
	for (int i = 1; i < 10; i++) {
		cout << tree[i].valL << " " << tree[i].valR << " " << tree[i].flag << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	now = n - 1;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		g[p].push_back(i);
	}
	build();
	cout << solve() << "\n";
	int q;
	cin >> q;
	while (q--) {
		char type;
		int val;
		cin >> type >> val;
		if (type == 'a') {
			//print();
			upd_subtree(val);
			//print();
		} else {
			now = val;
		}

		cout << solve() << "\n";
	}
	//print();
	return 0;
}