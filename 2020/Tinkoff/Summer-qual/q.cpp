#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int u, len;
	edge() {
		u = 0, len = 0;
	}
	edge(int a, int b) {
		u = a, len = b;
	}
};

const int MAXN = 110, MAXK = 55;
int n, k;
vector<edge> g[MAXN];
int w[MAXN];

int sz[MAXN], h[MAXN];
int dp[MAXN][MAXK][MAXN], help[MAXN][MAXK];
bool used[MAXN][MAXK][MAXN];

int ans;

void read() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		int v, len;
		cin >> w[i] >> v >> len;
		g[v].push_back({i, len});
	}
}

void dfs(int v, int len) {
	h[v] = len;
	sz[v] = 1;
	for (auto i : g[v]) {
		dfs(i.u, i.len + len);
		sz[v] += sz[i.u];
	}
}

void make(int v, int cnt, int up) {
	if (sz[v] == 1) {
		dp[v][cnt][up] = w[v] * (h[v] - h[up]);
		return;
	}

	for (int i = 0; i <= cnt; i++) {
		int u = g[v][0].u;
		help[0][i] = dp[u][i][up];
		if (i > 0)
			chkmin(help[0][i], dp[u][i - 1][u]);
	}

	for (int i = 1; i < (int)g[v].size(); i++) {
		int u = g[v][i].u;
		for (int j = 0; j <= cnt; j++) {
			help[i][j] = help[i - 1][j] + dp[u][0][up];
			for (int x = 1; x <= cnt && j - x >= 0; x++) {
				chkmin(help[i][j], help[i - 1][j - x] + dp[u][x][up]);
				chkmin(help[i][j], help[i - 1][j - x] + dp[u][x - 1][u]);
			}
		}
	}

	dp[v][cnt][up] = help[(int)g[v].size() - 1][cnt] + w[v] * (h[v] - h[up]);
}

void calc(int v, int cnt, int up) {
	if (sz[v] - 1 < cnt) return;
	if (used[v][cnt][up]) return;
	used[v][cnt][up] = true;
	for (auto i : g[v]) {
		for (int j = 0; j <= cnt; j++) {
			calc(i.u, j, up);
			if (j > 0)
				calc(i.u, j - 1, i.u);
		}
	}
	make(v, cnt, up);
}

void run() {
	dfs(0, 0);
	calc(0, k, 0);
	ans = dp[0][k][0];
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