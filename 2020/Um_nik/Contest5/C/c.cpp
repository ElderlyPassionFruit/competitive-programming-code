#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 2e3 + 10;

int n;
bool g[MAXN][MAXN];
bool used[MAXN], used2[MAXN];

void dfs(int v) {
	used[v] = true;
	for (int i = 0; i < n; i++) {
		if (!used[i] && g[v][i]) {
			dfs(i);
		}
	}
}

void dfs2(int v) {
	used2[v] = true;
	for (int i = 0; i < n; i++) {
		if (!used2[i] && g[i][v]) {
			dfs2(i);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			g[i][j] = x > 0;
		}
	}
	dfs(0);
	dfs2(0);
	bool ok = true;
	for (int i = 0; i < n; i++) {
		ok &= used[i] && used2[i];
	}
	cout << (ok ? "YES" : "NO");
	return 0;
}