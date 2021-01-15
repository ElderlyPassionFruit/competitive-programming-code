#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

int n;
vector<vector<bool>> g;

bool check(int mask) {
	vector<bool> used(n, true);
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			for (int j = 0; j < n; j++) {
				used[j] = used[j] && g[i][j];
			}
		}
	}
	int cnt = 0;
	for (auto i : used) cnt += i;
	return cnt == 1;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	for (int it = 0; ; it++) {
		n = get(2, 12);
		//int k = get(1, n - 1);
		int k = 2;
		g.assign(n, vector<bool> (n, false));
		int m = get(1, 100);
		for (int i = 0; i < m; i++) {
			int u = get(0, n - 2);
			int v = get(u + 1, n - 1);
			g[u][v] = g[v][u] = true; 
		}
		bool ok = true;
		for (int mask = 0; mask < (1 << n); mask++) {
			if (__builtin_popcount(mask) == k) {
				ok &= check(mask);
			}
		}
		if (ok) {
			//cout << "find! " << it << endl;
			cout << n << " " << k << endl;
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if (!g[i][j]) cout << -1 << " ";
					else cout << get(1, 10) << " ";
					//cout << g[i][j] << " ";
				}
				cout << endl;
			}
			return 0;
			cout << "g = " << endl;
			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if (g[i][j]) {
						cout << i << " " << j << endl; 
					}
				}
			}
			return 0;
		}
		cerr << "now = " << it << " ok = " << ok << endl;
	}
	return 0;
}