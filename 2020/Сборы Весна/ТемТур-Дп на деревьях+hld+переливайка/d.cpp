#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e6 + 10;
int n;
vector<int> g[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int sz;
		cin >> sz;
		while (sz--) {
			int v;
			cin >> v;
			//cout << i + 1 << " " << v << endl;
			v--;
			g[i].push_back(v);
		}
	}
}

const int INF = -1e7 - 7;
vector<pair<int, int>> dp[MAXN];
int tin[MAXN], tout[MAXN], timer = 0;

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u]; 
}

void relax(int v) {
	sort(all(dp[v]));
	reverse(all(dp[v]));
}

void dfs_down(int v, int p) {
	tin[v] = timer++;
	dp[v].resize(3);
	for (int i = 0; i < 3; i++) {
		dp[v][i] = {INF, -1};
	}
	dp[v][0] = {0, v};
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_down(i, v);
		if (dp[v][2].first < dp[i][0].first + 1) {
			dp[v][2] = dp[i][0];
			dp[v][2].first++;
			relax(v);
		}
	}
	tout[v] = timer++;
}

void dfs_up(int v, int p) {
	for (auto i : g[v]) {
		if (i == p) continue;
		pair<int, int> nxt = {INF, -1};
		for (int j = 0; j < 3; j++) {
			if (dp[v][j].first == INF) continue;
			if (is_upper(i, dp[v][j].second)) continue;
			nxt = dp[v][j];
			break;
		}
		if (nxt.first == INF) continue;
		if (dp[i][2].first < nxt.first + 1) {
			dp[i][2] = nxt;
			dp[i][2].first++;
			relax(i);
		}
	}
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_up(i, v);
	}
}

int ans;
vector<int> fans;

void make_ans() {
	ans = 3 * INF;
	fans = {};
	for (int i = 0; i < n; i++) {
		if (dp[i][2].first == INF) continue;
		int have = dp[i][0].first + dp[i][1].first + dp[i][2].first;
		if (have < ans) continue;
		ans = have;
		fans = {dp[i][0].second, dp[i][1].second, dp[i][2].second};
	}
}

void run() {
	dfs_down(0, 0);
	/*cout << "dp = " << endl;
	for (int i = 0; i < n; i++) {
		for (auto [dist, to] : dp[i]) {
			cout << dist << " " << to << " | ";
		}
		cout << endl;
	}*/
	dfs_up(0, 0);
	make_ans();
}

void write() {
	for (auto i : fans)
		cout << i + 1 << " ";
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