#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int get(int n, int m, int x, int y, int type) {
	if (x <= 0 || x > n || y <= 0 || y > m) return 0;
	int ans = min(min(x, n - x + 1), min(y, m - y + 1));
	if ((x + y) % 2 != type) ans++;
	return ans;
}

/*
bool checkCell(int n, int m, int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};


int stupid(int n, int m) {
	vector<vector<int>> used(n, vector<int> (m, 0));
	int it = 0;
	int ans = 1e9;
	while (true) {
		bool ok = true;
		for (auto i : used) for (auto j : i) ok &= j > 0;
		if (ok) break;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (used[i][j]) continue;
				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k], ny = j + dy[k];
					if (!checkCell(n, m, nx, ny)) continue;
					
				}
			}
		}
	}
}
*/

vector<int> dx = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
vector<int> dy = {0, 1, -1, 0, 1, -1, 0, 1, -1};

void solve() {
	int n, m;
	cin >> n >> m;
	if (n == 1 && m == 1) {
		cout << 1 << endl;
	} else if (min(n, m) <= 2) {
		cout << 2 << endl;
	} else {
		int x = (n + 1) / 2;
		int y = (m + 1) / 2;
		int ans0 = 0;
		for (auto i : dx) {
			for (auto j : dy) {
				chkmax(ans0, get(n, m, x + i, y + j, 0));
			}
		}
		int ans1 = 0;
		for (auto i : dx) {
			for (auto j : dy) {
				chkmax(ans1, get(n, m, x + i, y + j, 1));
			}
		}
		cout << min(ans0, ans1) << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}