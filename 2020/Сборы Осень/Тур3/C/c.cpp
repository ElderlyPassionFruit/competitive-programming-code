#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;

int n;
vector<int> g[MAXN];
int p[MAXN];

void read() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> p[i];
		p[i]--;
		g[i].push_back(p[i]);
		g[p[i]].push_back(i);
	}
}

const int MAXLOG = 20;
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], timer = 0;

void dfs(int v, int p, int len) {
	tin[v] = timer++;
	h[v] = len++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v]) {
		if (i != p) {
			dfs(i, v, len);
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

int dist(int v, int u) {
	return h[v] + h[u] - 2 * h[lca(v, u)];
}

void build() {
	dfs(0, 0, 0);
}

vector<int> ans;

void run() {
	build();
	int u = 0, v = 0, len = 0;
	for (int i = 1; i < n; i++) {
		int fans1 = dist(i, u);
		int fans2 = dist(i, v);
		if (fans1 > len && fans1 >= fans2) {
			len = fans1;
			v = i;
		}
		else if (fans2 > len) {
			len = fans2;
			u = i;
		}
		ans.push_back(len);
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