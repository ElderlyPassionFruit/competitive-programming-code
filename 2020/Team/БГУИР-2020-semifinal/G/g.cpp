#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

vector<vector<int>> ans;
int cnt;
int n, m;
int r, c;

void stupid_paint(int x1, int x2, int y1, int y2) {
	if (x2 - x1 + 1 == 4) {
		for (int j = y1; j <= y2; j++) {
			cnt++;
			for (int i = x1; i <= x2; i++) {
				ans[i][j] = cnt;
			}
		}
	} else {
		assert(y2 - y1 + 1 == 4);
		for (int i = x1; i <= x2; i++) {
			cnt++;
			for (int j = y1; j <= y2; j++) {
				ans[i][j] = cnt;
			}
		}
	}
}

void paint_square(int x1, int y1) {
	cnt++;
	for (int i = x1; i <= x1 + 1; i++) {
		for (int j = y1; j <= y1 + 1; j++) {
			ans[i][j] = cnt;
		}
	}
}

void solve_3_3(int x1, int x2, int y1, int y2) {
	if (x1 == r && y1 == c) {
		paint_square(x1, y1 + 1);
		cnt++;
		ans[x1 + 1][y1] = cnt;
		ans[x2][y1] = cnt;
		ans[x2][y1 + 1] = cnt;
		ans[x2][y1 + 2] = cnt;
	} else if (x1 == r && y2 == c) {
		paint_square(x1, y1);
		cnt++;
		ans[x2][y1] = cnt;
		ans[x2][y1 + 1] = cnt;
		ans[x2][y2] = cnt;
		ans[x1 + 1][y2] = cnt;
	} else if (x2 == r && y1 == c) {
		paint_square(x1, y1);
		cnt++;
		ans[x1][y2] = cnt;
		ans[x1 + 1][y2] = cnt;
		ans[x2][y2] = cnt;
		ans[x2][y1 + 1] = cnt;
	} else if (x2 == r && y2 == c) {
		paint_square(x1, y1 + 1);
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1 + 1][y1] = cnt;
		ans[x2][y1] = cnt;
		ans[x2][y1 + 1] = cnt;
	} else if (x1 + 1 == r && y1 + 1 == c) {
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1][y1 + 1] = cnt;
		ans[x1][y1 + 2] = cnt;
		ans[x1 + 1][y1] = cnt;

		cnt++;
		ans[x2][y1] = cnt;
		ans[x2][y1 + 1] = cnt;
		ans[x2][y2] = cnt;
		ans[x1 + 1][y2] = cnt;
	} else if (x1 == r && y1 + 1 == c) {
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1 + 1][y1] = cnt;
		ans[x2][y1] = cnt;
		ans[x1 + 1][y1 + 1] = cnt;

		cnt++;
		ans[x1][y2] = cnt;
		ans[x1 + 1][y2] = cnt;
		ans[x2][y2] = cnt;
		ans[x2][y2 - 1] = cnt;
	} else if (x2 == r && y1 + 1 == c) {
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1 + 1][y1] = cnt;
		ans[x2][y1] = cnt;
		ans[x1 + 1][y1 + 1] = cnt;

		cnt++;
		ans[x1][y2] = cnt;
		ans[x1 + 1][y2] = cnt;
		ans[x2][y2] = cnt;
		ans[x1][y2 - 1] = cnt;	
	} else if (x1 + 1 == r && y1 == c) {
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1][y1 + 1] = cnt;
		ans[x1][y2] = cnt;
		ans[x1 + 1][y1 + 1] = cnt;
	 	
		cnt++;
		ans[x2][y1] = cnt;
		ans[x2][y1 + 1] = cnt;
		ans[x2][y2] = cnt;
		ans[x1 + 1][y2] = cnt;
	} else if (x1 + 1 == r && y2 == c) {
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1][y1 + 1] = cnt;
		ans[x1][y2] = cnt;
		ans[x1 + 1][y1 + 1] = cnt;
	 	
		cnt++;
		ans[x2][y1] = cnt;
		ans[x2][y1 + 1] = cnt;
		ans[x2][y2] = cnt;
		ans[x1 + 1][y1] = cnt;
	} else {
		assert(false);
	}
}

void solve_3_7(int x1, int x2, int y1, int y2) {
	assert(y1 + 3 == c);
	if (x1 == r) {
		paint_square(x1, y1 + 1);
		paint_square(x1, y1 + 4);
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1 + 1][y1] = cnt;
		ans[x1 + 2][y1] = cnt;
		ans[x1 + 2][y1 + 1] = cnt;

		cnt++;
		ans[x1][y2] = cnt;
		ans[x1 + 1][y2] = cnt;
		ans[x1 + 2][y2] = cnt;
		ans[x1 + 2][y2 - 1] = cnt;

		cnt++;
		ans[x2][y1 + 2] = cnt;
		ans[x2][y1 + 3] = cnt;
		ans[x2][y1 + 4] = cnt;
		ans[x2 - 1][y1 + 3] = cnt;
	} else if (x1 + 1 == r) {
		paint_square(x1, y1 + 1);
		paint_square(x2 - 1, y2 - 1);
		
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1 + 1][y1] = cnt;
		ans[x1 + 2][y1] = cnt;
		ans[x1 + 2][y1 + 1] = cnt;
	
		cnt++;
		ans[x2][y1 + 2] = cnt;
		ans[x2][y1 + 3] = cnt;
		ans[x2][y1 + 4] = cnt;
		ans[x2 - 1][y1 + 4] = cnt;

		cnt++;
		ans[x1][y1 + 3] = cnt;
		ans[x1][y1 + 4] = cnt;
		ans[x1][y1 + 5] = cnt;
		ans[x1][y1 + 6] = cnt;
	} else if (x2 == r) {
		paint_square(x1 + 1, y1 + 1);
		paint_square(x1 + 1, y1 + 4);
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1 + 1][y1] = cnt;
		ans[x1 + 2][y1] = cnt;
		ans[x1][y1 + 1] = cnt;

		cnt++;
		ans[x1][y2] = cnt;
		ans[x1 + 1][y2] = cnt;
		ans[x1 + 2][y2] = cnt;
		ans[x1][y2 - 1] = cnt;

		cnt++;
		ans[x1][y1 + 2] = cnt;
		ans[x1][y1 + 3] = cnt;
		ans[x1][y1 + 4] = cnt;
		ans[x1 + 1][y1 + 3] = cnt;
	} else {
		assert(false);
	}
}

void solve_7_3(int x1, int x2, int y1, int y2) {
	assert(x1 + 3 == r);
	if (y1 == c) {
		paint_square(x1 + 1, y1);
		paint_square(x1 + 4, y1);

		cnt++;
		ans[x1][y1] = cnt;
		ans[x1][y1 + 1] = cnt;
		ans[x1][y1 + 2] = cnt;
		ans[x1 + 1][y1 + 2] = cnt;

		cnt++;
		ans[x2][y1] = cnt;
		ans[x2][y1 + 1] = cnt;
		ans[x2][y1 + 2] = cnt;
		ans[x2 - 1][y1 + 2] = cnt;
	
		cnt++;
		ans[x1 + 2][y2] = cnt;
		ans[x1 + 3][y2] = cnt;
		ans[x1 + 4][y2] = cnt;
		ans[x1 + 3][y2 - 1] = cnt;
	} else if (y1 + 1 == c) {
		paint_square(x2 - 1, y2 - 1);

		cnt++;
		ans[x1][y1] = cnt;
		ans[x1 + 1][y1] = cnt;
		ans[x1 + 2][y1] = cnt;
		ans[x1 + 3][y1] = cnt;

		cnt++;
		ans[x1 + 1][y2] = cnt;
		ans[x1 + 2][y2] = cnt;
		ans[x1 + 3][y2] = cnt;
		ans[x1 + 4][y2] = cnt;

		cnt++;
		ans[x1][y1 + 1] = cnt;
		ans[x1 + 1][y1 + 1] = cnt;
		ans[x1 + 2][y1 + 1] = cnt;
		ans[x1][y2] = cnt;

		cnt++;
		ans[x2][y1] = cnt;
		ans[x2 - 1][y1] = cnt;
		ans[x2 - 2][y1] = cnt;
		ans[x2 - 2][y1 + 1] = cnt;
	} else if (y2 == c) {
		paint_square(x1 + 1, y1 + 1);
		paint_square(x1 + 4, y1 + 1);

		cnt++;
		ans[x1][y1] = cnt;
		ans[x1][y1 + 1] = cnt;
		ans[x1][y1 + 2] = cnt;
		ans[x1 + 1][y1] = cnt;

		cnt++;
		ans[x2][y1] = cnt;
		ans[x2][y1 + 1] = cnt;
		ans[x2][y1 + 2] = cnt;
		ans[x2 - 1][y1] = cnt;
	
		cnt++;
		ans[x1 + 2][y1] = cnt;
		ans[x1 + 3][y1] = cnt;
		ans[x1 + 4][y1] = cnt;
		ans[x1 + 3][y1 + 1] = cnt;
	} else {
		assert(false);
	}
}

void solve_5_5(int x1, int x2, int y1, int y2) {
	if (x1 + 2 >= r && y1 + 2 >= c) {
		for (int add = 0; add <= 2; add += 2)
			paint_square(x1 + add, y1 + 3);
		paint_square(x1 + 3, y1);
		cnt++;
		ans[x1 + 3][y1 + 2] = cnt;
		ans[x2][y1 + 2] = cnt;
		ans[x2][y1 + 3] = cnt;
		ans[x2][y2] = cnt;
		solve_3_3(x1, x2 - 2, y1, y2 - 2);
	} else if (x1 + 2 >= r && y2 - 2 <= c) {
		for (int add = 0; add <= 2; add += 2) 
			paint_square(x1 + add, y1);
		paint_square(x2 - 1, y2 - 1);
		cnt++;
		ans[x2][y1] = cnt;
		ans[x2][y1 + 1] = cnt;
		ans[x2][y1 + 2] = cnt;
		ans[x2 - 1][y1 + 2] = cnt;
		solve_3_3(x1, x2 - 2, y1 + 2, y2);
	} else if (x2 - 2 <= r && y1 + 2 >= c) {
		for (int add = 0; add <= 2; add += 2)
			paint_square(x1, y1 + add);
		paint_square(x2 - 1, y2 - 1);
		cnt++;
		ans[x1][y2] = cnt;
		ans[x1 + 1][y2] = cnt;
		ans[x1 + 2][y2] = cnt;
		ans[x1 + 2][y2 - 1] = cnt;
		solve_3_3(x1 + 2, x2, y1, y2 - 2);
	} else if (x2 - 2 <= r && y1 - 2 <= c) {
		for (int add = 1; add <= 3; add += 2)
			paint_square(x1, y1 + add);
		paint_square(x2 - 1, y1);
		cnt++;
		ans[x1][y1] = cnt;
		ans[x1 + 1][y1] = cnt;
		ans[x1 + 2][y1] = cnt;
		ans[x1 + 2][y1 + 1] = cnt;
		solve_3_3(x2 - 2, x2, y2 - 2, y2);
	} else {
		assert(false);
	}
}

void solve_7_7(int x1, int x2, int y1, int y2) {
	assert(r == x1 + 3);
	assert(c == y1 + 3);
	for (int add = 1; add <= 5; add += 2)
		paint_square(x1, y1 + add);
	for (int add = 3; add <= 5; add += 2) 
		paint_square(x1 + add, y1);
	cnt++;
	ans[x1][y1] = cnt;
	ans[x1 + 1][y1] = cnt;
	ans[x1 + 2][y1] = cnt;
	ans[x1 + 2][y1 + 1] = cnt;
	solve_5_5(x1 + 2, x2, y1 + 2, y2);
}

void solve(int x1, int x2, int y1, int y2) {
	int lenX = x2 - x1 + 1;
	int lenY = y2 - y1 + 1;
	if (x1 + 4 <= r && lenX > 5) {
		stupid_paint(x1, x1 + 3, y1, y2);
		solve(x1 + 4, x2, y1, y2);
	} else if (x2 - 4 >= r && lenX > 5) {
		stupid_paint(x2 - 3, x2, y1, y2);
		solve(x1, x2 - 4, y1, y2);
	} else if (y1 + 4 <= c && lenY > 5) {
		stupid_paint(x1, x2, y1, y1 + 3);
		solve(x1, x2, y1 + 4, y2);
	} else if (y2 - 4 >= c && lenY > 5) {
		stupid_paint(x1, x2, y2 - 3, y2);
		solve(x1, x2, y1, y2 - 4);
	} else if (lenX == 3 && lenY == 3) {
		solve_3_3(x1, x2, y1, y2);
	} else if (lenX == 3 && lenY == 7) {
		solve_3_7(x1, x2, y1, y2);
	} else if (lenX == 5 && lenY == 5) {
		solve_5_5(x1, x2, y1, y2);
	} else if (lenX == 7 && lenY == 3) {
		solve_7_3(x1, x2, y1, y2);
	} else if (lenX == 7 && lenY == 7) {
		solve_7_7(x1, x2, y1, y2);
	} else {
		assert(false);
	}
}

void solve() {
	cin >> n >> m >> r >> c;
	r--;
	c--;
	if (n * m % 4 != 1) {
		cout << "NO" << "\n";
		return;
	}

	if (n == 1) {
		if (c % 4) {
			cout << "NO\n";
			return;
		}
		cout << "YES\n";
		cnt = 0;
		for (int i = 0; i < m; i += 4) {
			if (i == c) {
				cout << 0 << " ";
				continue;
			}
			cnt++;
			for (int j = 0; j < 4; j++) {
				cout << cnt << " ";
			}
		}
		cout << "\n";
		return;
	}

	if (m == 1) {
		if (r % 4) {
			cout << "NO\n";
			return;
		}
		cout << "YES\n";
		cnt = 0;
		for (int i = 0; i < n; i += 4) {
			if (i == r) {
				cout << 0 << " ";
				continue;
			}
			cnt++;
			for (int j = 0; j < 4; j++) {
				cout << cnt << " ";
			}
		}
		cout << "\n";
		return;
	}

	ans.assign(n, vector<int> (m, 0));
	cnt = 0;
	solve(0, n - 1, 0, m - 1);
	int have = 0;
	for (auto i : ans) {
		for (auto j : i) {
			have += j == 0;
		}
	}
	assert(have == 1);
	cout << "YES" << "\n";
	for (auto i : ans) {
		for (auto j : i) {
			cout << j << " "; 
		}
		cout << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}

/*
2
9 5 1 3
7 7 4 3
*/