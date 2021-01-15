#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e6 + 10;
int n, root;

vector<int> g[MAXN];
int col[MAXN];

int last[MAXN];
bool used[MAXN];
vector<int> q[MAXN * 2];

int timer = 0, ed[MAXN * 2], h[MAXN];

int st[MAXN * 2], pos = -1;
int par[MAXN * 2], sz[MAXN * 2], fans[MAXN * 2];

int fsum[MAXN], ans[MAXN];

void dfs(int v, int p, int len) {
	h[v] = len++;
	ed[timer++] = v;
	for (auto i : g[v]) {
		if (i != p) {
			dfs(i, v, len);
			ed[timer++] = v;
		}
	}
}

void make() {
	for (int i = 0; i < timer; i++) {
		par[i] = i;
		sz[i] = 1;
		fans[i] = ed[i];
	}
}	

int get_par(int v) {
	if (v == par[v])
		return v;
	return par[v] = get_par(par[v]);
}

int get_min(int v) {
	return fans[get_par(v)];
}

void union_set(int v, int u) {
	v = get_par(v);
	u = get_par(u);
	if (u == v)
		return;
	if (sz[v] < sz[u])
		swap(v, u);
	sz[v] += sz[u];
	par[u] = v;
	if (h[fans[u]] < h[fans[v]])
		fans[v] = fans[u];
}

void solve() {
	make();
	for (int i = 0; i < timer; i++) {
		while (pos >= 0 && h[ed[st[pos]]] > h[ed[i]]) {
			union_set(st[pos], i);
			pos--;
		}
		for (auto j : q[i]) {
			int ans = get_min(j);
			fsum[ans]--;
		}
		pos++;
		st[pos] = i;
	}
}

void calc(int v, int p) {
	ans[v] = fsum[v];
	for (auto i : g[v]) {
		if (i != p) {
			calc(i, v);
			ans[v] += ans[i];
		}
	}
}

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p >> col[i];
		if (p == 0) {
			root = i;
			continue;
		}
		p--;
		g[i].push_back(p);
		g[p].push_back(i);
	}
}

void run() {
	for (int i = 0; i < MAXN; i++) {
		last[i] = -1;
		fsum[i] = 1;
	}

	dfs(root, root, 0);
	
	for (int i = 0; i < timer; i++) {
		if (!used[ed[i]]) {
			if (last[col[ed[i]]] != -1) {
				q[i].push_back(last[col[ed[i]]]);
			}
			used[ed[i]] = true;
		}
		last[col[ed[i]]] = i;
	}

	solve();
	calc(root, root);
}

void write() {
	for (int i = 0; i < n; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
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