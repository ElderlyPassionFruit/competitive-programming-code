#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;
vector<pair<int, int> > ed;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		ed.push_back({u - 1, v - 1});
	}
}

vector<vector<int>> g;

vector<bool> used;

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v])  {
		if (!used[i])
			dfs(i);
	}
}

bool check(int mask) {
	g.assign(n, {});
	int cnt = 0;
	for (int i = 0; i < m; i++) {
		if ((mask >> i) & 1) {
			g[ed[i].first].push_back(ed[i].second);
			g[ed[i].second].push_back(ed[i].first);
			cnt++;
		}
	}
	if (cnt != n - 1) {
		return 0;
	}
	used.assign(n, 0);
	dfs(0);
	for (auto i : used)
		if (!i) return false;
	return true;
}

int ans;

void run() {
	ans = 0;
	for (int i = 0; i < (1 << m); i++) {
		ans += check(i);
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