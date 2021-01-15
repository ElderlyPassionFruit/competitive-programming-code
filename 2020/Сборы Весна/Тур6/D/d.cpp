#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 1e6 + 10;
int n;
int d[MAXN];

void read() {
	cin >> n;
	for (int i = 1; i <= n - 1; i++)
		cin >> d[i];
}

int g[MAXN][2];
int L[MAXN], R[MAXN];
int timer = 1;
int rd[MAXN];
int pos = 1;

void dfs_build(int v, int l, int r) {
	//cout << v << " " << l << " " << r << endl;
	L[v] = l, R[v] = r;
	g[v][0] = g[v][1] = -1;
	if (l == r) return;
	rd[v] = d[pos];
	pos++;
	g[v][0] = timer + 1;
	dfs_build(++timer, l, rd[v]);
	g[v][1] = timer + 1;
	dfs_build(++timer, rd[v] + 1, r);	
}


const int MAXLOG = 20;
int tin[MAXN], tout[MAXN], dp[MAXN][MAXLOG], h[MAXN];

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

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (is_upper(v, u)) return v;
	if (is_upper(u, v)) return u;
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_upper(dp[v][i], u)) {
			v = dp[v][i];
		}
	}
	return dp[v][0];
}

void build() {
	dfs_build(1, 1, n);
	dfs_lca(1, 1, 0);
}

vector<int> now;

void dfs_get(int v, int l, int r) {
	//cout << v << " " << l << " " << r << endl;
	if (v == -1) return;
	if (L[v] > r) return;
	if (R[v] < l) return;
	if (l <= L[v] && R[v] <= r) {
		now.push_back(v);
		return;
	}
	dfs_get(g[v][0], l, r);
	dfs_get(g[v][1], l, r);
}

vector<int> get(int l, int r) {
	now.clear();
	dfs_get(1, l, r);
	return now;
}



int dist(int u, int v) {
	return h[u] + h[v] - 2 * h[lca(u, v)];
}

vector<int> ans;

void run() {
	build();
	int q;
	cin >> q;
	while (q--) {
		int u, l, r;
		cin >> u >> l >> r;
		auto x = get(l, r);
		//cout << "x = " << endl;
		//for (auto i : x)
		//	cout << i << " ";
		//cout << endl;
		ll fans = 0;
		for (auto i : x)
			fans += dist(u, i);
		ans.push_back(fans);
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