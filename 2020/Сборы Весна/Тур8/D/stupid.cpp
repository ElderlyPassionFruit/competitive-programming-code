#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segm{
	int l, r;
	segm() {}
	segm(int _l, int _r) {
		l = _l, r = _r;
	}
};

int n, k;
vector<segm> have;

void read() {
	cin >> n >> k;
	have.resize(k);
	for (auto &i : have) {
		cin >> i.l >> i.r;
	}
}

bool check_group_1() {
	return true;
}

namespace solver_group_1{
	int n, k;
	vector<segm> have;
	void init(int _n, int _k, vector<segm> _have) {
		n = _n, k = _k, have = _have;
	}
	void solve() {
		for (auto i : have) {
			if (i.l <= n && i.r >= n) {
				cout << "Full" << endl;
				cout << 1 << endl;
				exit(0);
			}
		}
		for (auto i : have) {
			for (auto j : have) {
				int mx = max(i.r, j.r) - min(i.l, j.l);
				int mn = max(i.l, j.l) - min(i.r, j.r);
				if (mn <= n && mx >= n) {
					cout << "Full" << endl;
					cout << 2 << endl;
					exit(0);
				}
			}
		}
		cout << "Hungry" << endl;
	}
};

bool check_group_2() {
	return n <= 1000;
}

namespace solver_group_2{
	int n, k;
	vector<segm> have;
	void init(int _n, int _k, vector<segm> _have) {
		n = _n, k = _k, have = _have;
	}
	const int MAXN = 1010;
	int dp[MAXN * 2][MAXN][2];

	bool check[MAXN * 2];

	void build() {
		for (int i = 0; i < MAXN * 2; i++) {
			for (int j = 0; j < MAXN; j++) {
				for (int k = 0; k < 2; k++) {
					dp[i][j][k] = n * 10;
				}
				check[j] = 0;
			}
		}
		dp[0][0][0] = 0;
		for (auto x : have) {
			for (int i = x.l; i <= x.r; i++) {
				check[i] = 1;
			}
		}
	}

	void solve() {
		build();
		for (int i = 1; i <= 2 * n; i++) {
			for (int j = 0; j <= min(n, i); j++) {
				for (int k = 0; k < 2; k++) {
					if (j > 0) {
						chkmin(dp[i][j][k], dp[i - 1][j - 1][k]);
					}
					if (check[i - 1]) {
						chkmin(dp[i][j][k], dp[i - 1][i - j][k ^ 1] + 1);
					}
				}
			}
		}
		int ans = min(dp[2 * n][n][0], dp[2 * n][n][1]);
		if (ans == n * 10) {
			cout << "Hungry" << endl;
		} else {
			cout << "Full" << endl;
			cout << ans << endl;
		}
	}
};

void run() {
	if (check_group_2()) {
		solver_group_2::init(n, k, have);
		solver_group_2::solve();
	} else if (check_group_1()) {
		solver_group_1::init(n, k, have);
		solver_group_1::solve();
	}
}

void write() {

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