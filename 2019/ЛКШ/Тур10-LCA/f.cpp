#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10, MAXLOG = 21;
vector<int> g[MAXN];

int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN];
int timer = 0;

void dfs_lca(int v, int p, int len) {
	tin[v] = timer++;
	h[v] = len++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
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

struct event{
	int type, u, v;
};

vector<event> help;
int m;

void read() {
	cin >> m;
	int cnt = 1;
	for (int i = 0; i < m; i++) {
		char type;
		cin >> type;
		if (type == '+') {
			int v;
			cin >> v;
			v--;
			g[v].push_back(cnt);
			g[cnt].push_back(v);
			cnt++;
		}
		if (type == '-') {
			int v;
			cin >> v;
			v--;
			event a;
			a.type = 0;
			a.u = v;
			help.push_back(a);
		}
		if (type == '?') {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			event a;
			a.type = 1;
			a.u = u;
			a.v = v;
			help.push_back(a);
		}
	}
}

int sz[MAXN], par[MAXN], fans[MAXN];

void make() {
	for (int i = 0; i < m; i++) {
		sz[i] = 1;
		par[i] = i;
		fans[i] = i;
	}
}

int get_par(int v) {
	if (v == par[v])
		return v;
	return par[v] = get_par(par[v]);
}

void union_set(int a, int b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b)
		return;
	if (sz[a] < sz[b])
		swap(a, b);
	sz[a] += sz[b];
	par[b] = a;
	if (h[fans[a]] > h[fans[b]])
		fans[a] = fans[b];
}

vector<int> ans;

void run() {
	make();
	dfs_lca(0, 0, 0);
	for (auto i : help) {
		if (i.type == 0) {
			union_set(i.u, dp[i.u][0]);
		}
		else {
			int u = i.u;
			int v = i.v;
			int l = lca(u, v);
			ans.push_back(fans[get_par(l)]);
		}
	}
}

void write() {
	for (auto i : ans)
		cout << i + 1 << "\n";
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