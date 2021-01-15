#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int MAXN = 1e5 + 10;
vector <int> g[MAXN];
vector <pair <int, int> > help;
int n, k;
void read() {
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[i].push_back(p);
		g[p].push_back(i);
	}
	help.resize(k);
	for (int i = 0; i < k; i++) {
		cin >> help[i].first >> help[i].second;
		help[i].first--;
		help[i].second--;
	}
}

const int MAXLOG = 17;
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0, h[MAXN];

void dfs_lca(int v, int p, int len) {
	h[v] = len++;
	tin[v] = timer++;
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
	for (int i = MAXLOG - 1; i >= 0; i--)
		if (!is_upper(dp[v][i], u))
			v = dp[v][i];
	return dp[v][0];
}

int cross(int v1, int u1, int v2, int u2) {
	return max(0, h[lca(u1, u2)] - max(h[v1], h[v2]));
}

int ans = -1e9;
int ind1, ind2;
void run() {
	dfs_lca(0, 0, 0);
	for (int i = 0; i < k; i++) {
		for (int j = i + 1; j < k; j++) {
			int v1, u1, v2, u2;
			v1 = help[i].first;
			u1 = help[i].second;
			v2 = help[j].first;
			u2 = help[j].second;
			int l1 = lca(v1, u1);
			int l2 = lca(v2, u2);
			int fans = 0;

			fans += cross(l1, v1, l2, v2) + cross(l1, v1, l2, u2) + cross(l1, u1, l2, v2) + cross(l1, u1, l2, u2);
			if (fans > ans) {
				ans = fans;
				ind1 = i;
				ind2 = j;
			}
		}
	}
}


void run2() {
	dfs_lca(0, 0, 0);
	for (int i = 0; i < n; i++) {
		if (h[i] > 0 && g[i].size() == 0)
	}
}

void write() {
	cout << ans << endl;
	cout << ind1 + 1 << " " << ind2 + 1 << endl;
}

signed main() {
	freopen("twopaths.in", "r", stdin);
	freopen("twopaths.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}