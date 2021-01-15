#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<vector<int>> g;

void read() {
	cin >> n;
	g.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int ans;
vector<int> fans;

void dfs(int v, int len, vector<int> & used) {
	if (len == -1) return;
	used[v] = len--;
	for (auto i : g[v]) {
		if (used[i] < len) {
			dfs(i, len, used);
		}
	}
}

bool check(vector<int> have) {
	vector<int> used(n, -1);
	for (int i = 0; i < n; i++) {
		if (have[i] == 0) continue;
		dfs(i, have[i], used);
	}
	for (auto i : used) {
		if (i == -1) {
			return false;
		}
	}
	return true;
}

void recalc(vector<int> have) {
	if (!check(have)) return;
	int now = 0;
	for (auto i : have) {
		now += i;
	}
	if (ans <= now) return;
	/*cout << "have = " << endl;
	for (auto  i: have)
		cout << i << " ";
	cout << endl;*/
	ans = now;
	fans = have;
}

void solve(vector<int> have) {
	if (have.size() == n) {
		recalc(have);
		return;
	}
	have.push_back(0);
	solve(have);
	for (int i = 1; i <= n; i++) {
		have[have.size() - 1]++;
		solve(have);
	}
}

void run() {
	ans = 1e9;
	fans = {};
	//cout << check({1, 0, 0, 0, 0}) << endl;
	solve({});
}

void write() {
	cout << ans << endl;
	for (auto i : fans)
		cout << i << " ";
	cout << endl;
}

signed main() {
	//freopen("bus.in", "r", stdin);
	//freopen("bus.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}