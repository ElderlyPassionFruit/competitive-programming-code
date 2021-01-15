#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10, MAXLOG = 20;
vector<int> g[MAXN];
int w[MAXN];
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], h[MAXN], Max[MAXN][MAXLOG];
int timer = 0;

void dfs_lca(int v, int p, int len, int have) {
	tin[v] = timer++;
	h[v] = len++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];

	Max[v][0] = have;
	for (int i = 1; i < MAXLOG; i++)
		Max[v][i] = max(Max[v][i - 1], Max[dp[v][i - 1]][i - 1]);

	for (auto i : g[v])
		if (i != p)
			dfs_lca(i, v, len, w[v]);
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

int get_max(int v, int u) {
	int l = lca(v, u);
	int ans = w[l];
	while (v != l) {
		chkmax(ans, w[v]);
		v = dp[v][0];
	}
	while (u != l) {
		chkmax(ans, w[u]);
		u = dp[u][0];
	}

	//chkmax(ans, w[l]);
	/*for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_upper(dp[v][i], u)) {
			chkmax(ans, Max[v][i]);
			v = dp[v][i];
		}
	}
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!is_upper(dp[u][i], v)) {
			chkmax(ans, Max[u][i]);
			u = dp[u][i];
		}
	}*/
	return ans;
}

struct circle{
	int x, y, r;
};

int n, k;
vector <circle> help;

void read() {
	cin >> n >> k;
	help.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> help[i].x >> help[i].y >> help[i].r >> w[i];
	}
	w[n] = 0;
	help.push_back({0, 0, 100000});
	n++;
}

int sq(int a) {
	return a * a;
}

int dist(circle a, circle b) {
	return sq(a.x - b.x) + sq(a.y - b.y);
}

bool is_edge(int i, int j) {
	return dist(help[i], help[j]) < sq(max(help[i].r, help[j].r));
}

void build() {
	sort(help.begin(), help.end(), [&] (circle a, circle b) {return a.r < b.r;});
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (is_edge(i, j)) {
				g[i].push_back(j);
				g[j].push_back(i);
				break;
			}
		}
	}
	dfs_lca(0, 0, 0, -1e9);
}

int ans;

void run() {
	build();
	ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int my_max = max(w[i], w[j]);
			int have_max = get_max(i, j);
			if (my_max < have_max)
				continue;
			int len = dist(i, j);
			if (len > k)
				continue;
			chkmax(ans, abs(w[i] - w[j]));
		}
	}
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