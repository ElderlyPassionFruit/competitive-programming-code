#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1e5 + 10;
const int MAXLOG = 20;
int n, m, root;
set <int> g[MAXN], gr[MAXN];
int tin[MAXN], fup[MAXN], tout[MAXN], timer = 0, used[MAXN];
set <pair <int, int> > edges;
set <pair <int, int> > bridges;

pair <int, int> ed(int x, int y) {
	return {min(x, y), max(x, y)};
}

void is_bridge(int v, int u) {
	bridges.insert(ed(v, u));
}

void dfs_bridge(int v, int p) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) {
			fup[v] = min(fup[v], tin[i]);
		}
		else {
			dfs_bridge(i, v);
			fup[v] = min(fup[v], fup[i]);
			if (tin[v] < fup[i]) {
				is_bridge(v, i);
			}
		}
	}
}

int comp = 0;
int comps[MAXN];

bool check(int v, int u) {
	return bridges.find(ed(v, u)) == bridges.end();
}

void dfs_comp(int v) {
	used[v] = true;
	comps[v] = comp;
	for (auto i : g[v]) {
		if (check(i, v) && !used[i]) {
			dfs_comp(i);
		}
	}
}

void clear() {
	for (int i = 0; i < MAXN; i++) {
		used[i] = 0;
		tin[i] = 0;
		tout[i] = 0;
	}
	timer = 0;
}

int dp[MAXN][MAXLOG];
int h[MAXN];

void dfs_lca(int v, int p, int len) {
	//cout << "v = " << v << " p = " << p << " len = " << len << endl; 
	tin[v] = timer++;
	h[v] = len++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : gr[v]) {
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
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return dp[v][0];
}

void make() {
	clear();
	dfs_bridge(0, 0);
	clear();
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_comp(i);
			comp++;
		}
	}

/*	cout << "bridges = " << endl;
	for (auto i : bridges) {
		cout << i.first << " " << i.second << endl; 
	}
	cout << endl;
	cout << "comps = " << endl;
	for (int i = 0; i < n; i++) {
		cout << comps[i] << " ";
	}
	cout << endl;*/
	for (auto i : bridges) {
		gr[comps[i.first]].insert(comps[i.second]);
		gr[comps[i.second]].insert(comps[i.first]);
	}

	/*cout << "gr = " << endl;
	for (int i = 0; i < comp; i++) {
		for (auto j : g[i]) {
			cout << i << " " << j << endl;
		}
	}

	cout << endl;
*/
	clear();
	dfs_lca(comps[root], comps[root], 0);
	//cout << "puhh" << endl;
}


void read() {
	cin >> n >> m >> root;
	root--;
	for (int i = 0; i < m; i++) {
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		g[v].insert(u);
		g[u].insert(v);
		edges.insert(ed(v, u));
	}
	make();
}

vector <int> ans;

void run() {
	int q;
	cin >> q;
	for (int test = 0; test < q; test++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		a = comps[a];
		b = comps[b];
		int l = lca(a, b);
		int fans = h[l];
		ans.push_back(fans);
	}
}

void write() {
	for (auto i : ans)
		cout << i << '\n';
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