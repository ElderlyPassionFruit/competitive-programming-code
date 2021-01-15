#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0) {
		a += MOD;
	}
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

pair<int, int> dfs(int v, vector<vector<int>> & g) {
	pair<int, int> ans = {0, 0};
	for (auto i : g[v]) {
		pair<int, int> fans = dfs(i, g);
		ans.first += fans.second;
		ans.second += fans.first;
	}
	if (g[v].size() == 3) ans.first++;
	return ans;
}

int stupidSolve(int n) {
	vector<vector<int>> g(1);
	for (int i = 1; i < n; i++) {
		//cout << "it = " << i << endl;
		for (int j = (int)g.size() - 1; j >= 0; j--) {
			if (g[j].size() == 0) {
				g[j].push_back(g.size());
				g.push_back({});
			} else if (g[j].size() == 1) {
				g[j].push_back(g.size());
				g.push_back({});
				g[j].push_back(g.size());
				g.push_back({});
			}
		}
	}
	pair<int, int> fans = dfs(0, g);
	cout << n << " " << (fans.first < fans.second) << endl;
	return max(fans.first, fans.second);
	for (int i = 0; i < (int)g.size(); i++) {
		if (g[i].size() != 3) continue;
		for (auto j : g[i]) {
			cout << i << " " << j << endl;
		}
	}
}

const int MAXN = 2e6 + 10;

int dp[MAXN];
int pows[MAXN];

void precalc() {
	for (int i = 1; i < 30; i++) {
		dp[i] = stupidSolve(i);
		//cout << dp[i] << " ";
	}
	cout << endl;
}

void solve() {
	int n;
	cin >> n;
	cout << dp[n] << endl;
	//stupidSolve(n);
	//exit(0);
	/*if (n <= 2) {
		cout << 0 << endl;
	} else {
		cout << mul(dp[n - 1], 4) << endl;
	}
	return;
	if (n <= 2) {
		cout << 0 << endl;
	} else if (n <= 4) {
		cout << 4 << endl;
	} else {
		n -= 2;
		cout << sub(mul(2, mul(n, n)), mul(2, n)) << endl;
	}*/
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	precalc();
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}