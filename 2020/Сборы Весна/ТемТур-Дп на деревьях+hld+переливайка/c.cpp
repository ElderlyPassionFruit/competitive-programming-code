#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n;
vector<int> g[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int len = 0;
vector<vector<int>> ans;

void relax(int new_len, vector<vector<int>> fans) {
	if (new_len <= len) return;
	len = new_len;
	ans = fans;
}

struct fdp{
	int len, v;
	fdp() {}
	fdp(int _len, int _v) {
		len = _len, v = _v;
	}
};

bool operator<(const fdp & a, const fdp & b) {
	return tie(a.len, a.v) < tie(b.len, b.v);
}

fdp dp[MAXN][3];

void relax(int v) {
	if (dp[v][0] < dp[v][1]) {
		swap(dp[v][0], dp[v][1]);
	}
	if (dp[v][0] < dp[v][2]) {
		swap(dp[v][0], dp[v][2]);
	}
	if (dp[v][1] < dp[v][2]) {
		swap(dp[v][1], dp[v][2]);
	}	
}

int tin[MAXN], tout[MAXN], timer = 0;

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

pair<int, vector<int>> best[MAXN];

void dfs_down(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = {0, v};
	dp[v][1] = {-1, -1};
	dp[v][2] = {-1, -1};

	pair<int, vector<int>> mx1 = {-1, {}}, mx2 = {-1, {}};

	for (auto to : g[v]) {
		if (to == p) continue;
		dfs_down(to, v);
		chkmax(mx2, best[to]);
		if (mx1 < mx2) {
			swap(mx1, mx2);
		}

		if (dp[to][0].len + 1 <= dp[v][2].len) continue;
		dp[v][2] = dp[to][0];
		dp[v][2].len++;
		relax(v);
	}
	tout[v] = timer++;

	if (mx2.first != -1) {
		relax(mx1.first + mx2.first, {mx1.second, mx2.second});
	}

	relax(dp[v][0].len + 1, {{dp[v][0].v, v}});
	best[v] = {dp[v][0].len + 1, {{dp[v][0].v, v}}};
	if (dp[v][1].len == -1) return;
	best[v] = {dp[v][0].len + dp[v][1].len + 1, {{dp[v][0].v, dp[v][1].v}}};
	relax(dp[v][0].len + dp[v][1].len + 1, {{dp[v][0].v, dp[v][1].v}});
}

fdp make_nxt(int v, int to, fdp nxt) {
	if (nxt.len != -1) {
		nxt.len++;
	}
	fdp have;
	have = {-1, -1};
	if (is_upper(to, dp[v][0].v)) {
		have = dp[v][1];
	} else {
		have = dp[v][0];
	}
	if (have.len != -1) {
		have.len++;
	}
	return max(have, nxt);
}

pair<int, vector<int>> make_path(int v, int to, fdp nxt, int new_len, vector<int> fans) {
	fdp have[2];
	have[0] = {-1, -1};
	have[1] = {-1, -1};
	if (dp[v][0].v != -1 && is_upper(to, dp[v][0].v)) {
		have[0] = dp[v][1];
		have[1] = dp[v][2];
	} else if (dp[v][1].v != -1 && is_upper(to, dp[v][1].v)) {
		have[0] = dp[v][0];
		have[1] = dp[v][2];	
	} else {
		have[0] = dp[v][0];
		have[1] = dp[v][1];
	}
	assert(!(have[0] < have[1]));
	
	chkmax(have[1], nxt);
	if (have[0] < have[1]) {
		swap(have[0], have[1]);
	}

	pair<int, vector<int>> ans = {new_len, fans};
	if (have[0].len != -1) {
		pair<int, vector<int>> fans = {have[0].len + 1, {have[0].v, v}};
		chkmax(ans, fans);
	}

	if (have[0].len != -1 && have[1].len != -1) {
		pair<int, vector<int>> fans = {have[0].len + have[1].len + 1, {have[0].v, have[1].v}};
		chkmax(ans, fans);
	}
	return ans;
}

void dfs_up(int v, int p, fdp nxt, int new_len, vector<int> fans) {
	if (new_len != -1) {
		relax(dp[v][0].len + 1 + new_len, {fans, {v, dp[v][0].v}});
		if (dp[v][1].len != -1) {
			relax(dp[v][0].len + dp[v][1].len + 1 + new_len, {fans, {dp[v][0].v, dp[v][1].v}});
		}
	}

	for (auto to : g[v]) {
		if (to == p) continue;
		auto Nxt = make_nxt(v, to, nxt);
		auto path = make_path(v, to, nxt, new_len, fans);
		dfs_up(to, v, Nxt, path.first, path.second);
	}
}

void run() {
	dfs_down(0, 0);
	dfs_up(0, 0, {-1, -1}, -1, {});
}

void write() {
	cout << len << endl;
	if ((int)ans.size() == 2) {
		swap(ans[0][0], ans[1][0]);
	}
	for (auto i : ans) {
		for (auto j : i) {
			cout << j + 1 << " ";
		}
		cout << endl;
	}
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


/*

PE 137
input = 
8
1 2
2 3
3 4
4 5
5 6
4 7
7 8

out = 
7
8 3 
1 6 

*/