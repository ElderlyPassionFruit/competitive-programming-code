#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const int MAXN = 1e5 + 1;
const int inf = -1e9;

int tin[MAXN];
int tout[MAXN];

int pid[MAXN];
int hv[MAXN];

int pr[MAXN];
int sz[MAXN];
int d[MAXN];

int timer = 0;
int  place[MAXN];
int pathsz[MAXN];
int t[4 * MAXN];
vector<int> g[MAXN];

void upd(int v, int l, int r, int ql, int qr, int x) {
	if (l >= qr || ql >= r) return;
	if (l >= ql && r <= qr) {
		t[v] += x;
		return;
	}
	upd(2 * v + 1, l, (l + r) / 2, ql, qr, x);
	upd(2 * v + 2, (l + r) / 2, r, ql, qr, x);
	t[v] = max(t[2 * v + 1], t[2 * v + 2]);
}

int get(int v, int l, int r, int ql, int qr) {
	if (l >= qr || ql >= r) return -inf;
	if (l >= ql && r <= qr) {
		return t[v];
	}
	int g1 = get(2 * v + 1, l, (l + r) / 2, ql, qr);
	int g2 = get(2 * v + 2, (l + r) / 2, r, ql, qr);
	return max(g1, g2);
}

int text[MAXN];

void dfs(int v, int p) {
	sz[v] = 1;
	tin[v] = timer++;
	pr[v] = p;
	for (int i : g[v]) {
		if (i == p) continue;
		d[i] = d[v] + 1;
		dfs(i, v);
		sz[v] += sz[i];
		if (sz[i] > sz[text[v]]) text[v] = i;
	}
	tout[v] = timer++;
}

int cnt = 0;
int ns = 0;

void dfsbuild(int v, int p) {
	pid[v] = cnt;
	if (!pathsz[cnt]) {
		hv[cnt] = v;
	}
	++pathsz[cnt];
	place[v] = ns++;
	if (text[v] > 0) dfsbuild(text[v], v);
	for (int i : g[v]) {
		if (i == p || i == text[v]) continue;
		++cnt;
		dfsbuild(i, v);
	}
}

int get(int a, int b) {
	int ans = 0;
	while (pid[a] ^ pid[b]) {
		if (d[hv[pid[a]]] < d[hv[pid[b]]]) swap(a, b);
		ans = max(ans, get(0, 0, MAXN, place[hv[pid[a]]], place[a] + 1));
		a = pr[hv[pid[a]]];
	}
	if (d[a] > d[b]) swap(a, b);
	ans = max(ans, get(0, 0, MAXN, place[a], place[b] + 1));
	return ans;
}

void upd(int v, int x) {
	upd(0, 0, MAXN, place[v], place[v] + 1, x);
}

signed main() {
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, 1);
	dfsbuild(1, 1);
	int q;
	cin >> q;
	while (q--) {
		char c;
		cin >> c;
		if (c == '!') {
			int v, x;
			cin >> v >> x;
			upd(v, x);
		}
		else {
			int v, u;
			cin >> v >> u;
			cout << get(v, u) << '\n';
		}
	}
}