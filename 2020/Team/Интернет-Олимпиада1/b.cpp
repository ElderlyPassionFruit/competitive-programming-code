#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

//Пусть dp[i][0] - ответ, если мы уничтожаем поддерево полностью
// dp[i][1] - ответ, если мы уничтожаем поддерево, но всё, что осталось цвета 1
// dp[i][2] - ответ ... цвета 2
const int INF = 1e9 + 10;
const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
int dp[MAXN][3];
int col[MAXN];
int n;

void dfs(int v, int p) {
	dp[v][0] = dp[v][1] = dp[v][2] = INF;
	for (auto i : g[v]) {
		if (i != p) {
			dfs(i, v);
		}
	}

	// Пусть мы не меняем цвет вершины и считаем dp[v][0]
	int x = 1;
	for (auto i : g[v]) {
		if (i != p) {
			x += min(dp[i][0], dp[i][col[v]]);
		}
	}
	dp[v][0] = min(dp[v][0], x);

	x = 2;
	for (auto i : g[v]) {
		if (i != p) {
			x += min(dp[i][0], dp[i][col[v] ^ 3]);
		}
	}
	dp[v][0] = min(dp[v][0], x);

	// dp[v][col[v]]
	x = 0;
	for (auto i : g[v]) {
		if (i != p) {
			x += min(dp[i][0], dp[i][col[v]]);
		}
	}

	dp[v][col[v]] = min(dp[v][col[v]], x);

	x = 1;
	for (auto i : g[v]) {
		if (i != p) {
			x += min(dp[i][0], dp[i][col[v] ^ 3]);
		}
	}

	dp[v][col[v] ^ 3] = min(dp[v][col[v] ^ 3], x);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		char x;
		cin >> x;
		col[i] = (x - '0') + 1;
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0, 0);
	cout << dp[0][0] << endl;
	return 0;
}












