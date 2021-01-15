#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 20, MAXLOG = 17;
int n, k;
int c[MAXN];
vector<int> g[MAXN], gr[MAXN];
int last[MAXN], tin[MAXN], tout[MAXN], dp[MAXN][MAXLOG], h[MAXN], timer = 0;
int par[MAXN], val[MAXN];

void read() {
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		cin >> c[i];
		c[i]--;
	}
}

void make() {
	for (int i = 0; i < n; i++) {
		par[i] = i, val[i] = i;
	}
}

int get_par(int v) {
	if (v == par[v]) return v;
	return par[v] = get_par(par[v]);
}

void uni(int a, int b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b) return;
	par[b] = a;
	if (h[val[a]] > h[val[b]]) val[a] = val[b];
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

void dfs_lca(int v, int p, int len) {
	tin[v] = timer++;
	dp[v][0] = p;
	h[v] = len++;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_lca(i, v, len);
	}
	tout[v] = timer++;
}

void Add(int up, int down) {
	//cout << "Add = " << up << " " << down << endl; 
	int real = down;
	while (h[down] > h[up]) {
		//cout << c[real] << " " << c[dp[down][0]] << endl;
		gr[c[real]].push_back(c[dp[down][0]]);
		uni(real, dp[down][0]);
		down = val[get_par(down)];
	}
}

void add(int u, int v) {
	int l = lca(u, v);
	Add(l, u);
	Add(l, v);
}

void dfs(int v, int p) {
	if (last[c[v]] != -1) {
		add(last[c[v]], v);
	}
	last[c[v]] = v;

	for (auto i : g[v]) {
		if (i == p) continue;
		dfs(i, v);
		last[c[v]] = v;
	}
}

void build() {
	dfs_lca(0, 0, 0);	
	for (int i = 0; i < k; i++)
		last[i] = -1;
	dfs(0, 0);
}

vector<int> order;
vector<bool> used;

void dfs_order(int v) {
	used[v] = true;
	for (auto i : gr[v]) {
		if (used[i]) continue;
		dfs_order(i);
	}
	order.push_back(v);
}

vector<int> cnt;
vector<int> color;

void dfs_color(int v, int c) {
	cnt[cnt.size() - 1]++;
	color[v] = c;
	used[v] = true;
	for (auto i : g[v]) {
		if (used[i]) continue;
		dfs_color(i, c);
	} 
}

int ans;

void calc() {
	for (int i = 0; i < k; i++) {
		g[i].clear();
	}
	for (int i = 0; i < k; i++) {
		for (auto j : gr[i]) {
			g[j].push_back(i);
		}
	}


	/*cout << "gr = " << endl;
	for (int i = 0; i < k; i++) {
		cout << "i = " << i << endl;
		for (auto j : gr[i]) {
			cout << j << " ";
		}
		cout << endl;
	}*/

	used.assign(k, false);
	for (int i = 0; i < k; i++) {
		if (used[i]) continue;
		dfs_order(i);
	}
	reverse(all(order));
	used.assign(k, false);
	color.assign(k, 0);
	int c = 0;
	for (auto i : order) {
		if (used[i]) continue;
		cnt.push_back(0);
		dfs_color(i, c++);
	}

	/*cout << "color = " << endl;
	for (auto i : color)
		cout << i << " ";
	cout << endl;

	cout << "cnt = " << endl;
	for (auto i : cnt)
		cout << i << " ";
	cout << endl;*/

	vector<bool> good(c, true);
	for (int i = 0; i < k; i++) {
		for (auto j : gr[i]) {
			int u = color[i], v = color[j];
			if (u == v) continue;
			good[u] = false;
		}
	}

	/*cout << "good = " << endl;
	for (auto i : good) {
		cout << i << " ";
	}
	cout << endl;

	cout << "cnt = " << endl;
	for (auto i : cnt) {
		cout << i << " ";
	}
	cout << endl;*/

	ans = k - 1;
	for (int i = 0; i < c; i++) {
		if (good[i]) {
			chkmin(ans, cnt[i] - 1);
		}
	}
}

void run() {
	make();
	build();
	/*cout << "gr = " << endl;
	for (int i = 0; i < k; i++) {
		//cout << "V = " << i << endl;
		for (auto j : gr[i]) {
			cout << i << " " << j << endl;
		}
		cout << endl;
	}*/
	calc();
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