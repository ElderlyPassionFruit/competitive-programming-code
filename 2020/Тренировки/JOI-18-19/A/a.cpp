#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3010;
int n, m;
char table[MAXN][MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> table[i][j];
		}
	}
}

ll ans;

int dp[MAXN][MAXN][2];

void build() {
	for (int i = 0; i < n; i++) {
		dp[i][m - 1][0] = (int)(table[i][m - 1] == 'O');
		for (int j = m - 2; j >= 0; j--) {
			dp[i][j][0] = dp[i][j + 1][0] + (int)(table[i][j] == 'O');
		}
	}
	for (int j = 0; j < m; j++) {
		dp[n - 1][j][1] = table[n - 1][j] == 'I';
		for (int i = n - 2; i >= 0; i--) {
			dp[i][j][1] = dp[i + 1][j][1] + (int)(table[i][j] == 'I');
		}
	}

	/*cout << "dp = " << endl;
	for (int it = 0; it < 2; it++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << dp[i][j][it] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}*/
}

void calc() {
	ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (table[i][j] == 'J') {
				ans += dp[i][j][0] * dp[i][j][1];
			}
		}
	}
}

void run() {
	build();
	calc();
}

void write() {
	cout << ans << endl;
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