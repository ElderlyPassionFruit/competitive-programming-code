#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10;
vector<int> g[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int p;
		cin >> p;
		if (p == -1) continue;
		p--;
		g[i].push_back(p);
		g[p].push_back(i);
	}
}

bool used[MAXN];

int dp[MAXN][2];
int cost[MAXN];
bool flag[MAXN];

int dfs_cycle(int v, int p) {
	flag[v] = true;
	int ans = -1;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (flag[i]) return v;
		chkmax(ans, dfs_cycle(i, v));
	}
	return ans;
}

bool flag2[MAXN];

void dfs_calc(int v, int p) {
	flag2[v] = true;
	dp[v][0] = 0;
	dp[v][1] = cost[v];
	for (auto i : g[v]) {
		if (i == p) continue;
		if (used[i]) continue;
		dfs_calc(i, v);
		dp[v][0] += max(dp[i][0], dp[i][1]);
		dp[v][1] += dp[i][0];
	}
}

void clear(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i]) {
			clear(i);
		}
	}
}

void clear_flag2(int v) {
	flag2[v] = false;
	for (auto i : g[v]) {
		if (flag2[i]) {
			clear_flag2(i);
		}
	}
}

int calc(int v) {
	int x = dfs_cycle(v, -1);
	if (x == -1) {
		dfs_calc(v, -1);
		clear(v);
		return max(dp[v][0], dp[v][1]);
	}
	v = x;
	int ans = 0;

	int fans = 0;
	used[v] = true;
	for (auto i : g[v]) {
		if (!flag2[i]) {
			dfs_calc(i, v);
			fans += max(dp[i][0], dp[i][1]);
		}
	}
	chkmax(ans, fans);
	for (auto i : g[v]) {
		if (flag2[i]) {
			clear_flag2(i);
		}
	}
	for (auto i : g[v]) {
		cost[i] = 0;
	}
	fans = 1;
	for (auto i : g[v]) {
		if (!flag2[i]) {
			dfs_calc(i, v);
			fans += max(dp[i][0], dp[i][1]);
		}
	}
	chkmax(ans, fans);
	clear(v);
	return ans;
}

int ans;

void run() {
	ans = 0;
	for (int i = 0; i < n; i++) {
		cost[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			ans += calc(i);
			//cout << i << endl;
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