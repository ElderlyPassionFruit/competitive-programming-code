#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<int> p;
int ans;

void dfs(int v, vector<bool> & used, vector<vector<int>> & g, int & fans) {
	used[v] = true;
	fans++;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs(i, used, g, fans);
		}
	}
}

void calc(vector<int> p) {
	/*cout << "p = " << endl;
	for (auto i : p)
		cout << i << " ";
	cout << endl;*/
	vector<vector<int>> g(n);
	for (int i = 0; i < n; i++) {
		g[i].push_back(p[i]);
	}
	int fans = -n;
	for (int i = 0; i < n; i++) {
		vector<bool> used(n, false);
		dfs(i, used, g, fans);
	}
	//cout << fans << endl;
	ans = max(ans, fans);
}

void solve(vector<int> p, int pos) {
	if (pos == n) {
		calc(p);
		return;
	}
	if (p[pos] != -1) {
		solve(p, pos + 1);
		return;
	}
	for (int i = 0; i < n; i++) {
		p[pos] = i;
		solve(p, pos + 1);
	}
}

void solve() {
	cin >> n;
	ans = 0;
	p.assign(n, -1);
	for (auto &i : p) {
		cin >> i;
	}
	solve(p, 0);
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}