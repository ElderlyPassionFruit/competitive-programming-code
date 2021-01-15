#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;
vector<vector<int>> g;
vector<int> ans;
vector<bool> used;

void no() {
	cout << -1 << endl;
	exit(0);
}

vector<bool> used2;

void dfs_check(int v, int & sz, int & cnt_edges) {
	used2[v] = true;
	for (auto i : g[v]) {
		if (!used2[i]) {
			dfs_check(i, sz, cnt_edges);
		}
	}
	sz++;
	cnt_edges += g[v].size();
}

void check(int v) {
	int sz = 0, cnt_edges = 0;
	dfs_check(v, sz, cnt_edges);
	cnt_edges /= 2;
	if (cnt_edges < v) no();
}

void solve(int v) {

}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	g.reisze(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	ans.resize(n, 0);
	used.resize(n, false);
	used2.resize(n, false);
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			solve(i);
		}
	}
	cout << "TAK" << "\n";
	for (auto i : ans) {
		cout << i + 1 << "\n";
	}
	return 0;
}