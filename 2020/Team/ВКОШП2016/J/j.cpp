#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
const int INF = 1e9;
const int MAXN = 310;
int g[MAXN][MAXN];
int n, k;
vector<int> comp[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int cnt;
		cin >> cnt;
		while (cnt--) {
			int x;
			cin >> x;
			comp[x].push_back(i);
		}
	}

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			g[i][j] = INF;
		}
	}

	for (int i = 1; i <= k; i++) {
		for (auto j : comp[i]) {
			for (auto k : comp[i]) {
				g[j][k] = min(g[j][k], (int)comp[i].size() - 1);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		g[i][i] = 0;
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j] + 2);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << (g[i][j] != INF ? g[i][j] : -1) << " ";
		}
		cout << endl;
	}
	return 0;
}