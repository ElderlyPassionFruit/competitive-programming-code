#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2000;
int n, m;
char a[MAXN][MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
}

int dp[MAXN][MAXN][4];

bool checkX(int x) {
	return x >= 0 && x < n;
}

bool checkY(int y) {
	return y >= 0 && y < m;
}

void build(int id, int sI, int dI, int sJ, int dJ, int dx, int dy) {
	for (int i = sI; checkX(i); i += dI) {
		for (int j = sJ; checkY(j); j += dJ) {
			dp[i][j][id] = 1;
			if (!checkX(i + dx)) continue;
			if (!checkY(j + dy)) continue;
			if (a[i][j] != a[i + dx][j]) continue;
			if (a[i][j] != a[i][j + dy]) continue;
			dp[i][j][id] += min(dp[i + dx][j][id], dp[i][j + dy][id]);
		}
	}
}

void build() {
	build(0, 0, 1, 0, 1, -1, -1);
	build(1, 0, 1, m - 1, -1, -1, 1);
	build(2, n - 1, -1, 0, 1, 1, -1);
	build(3, n - 1, -1, m - 1, -1, 1, 1);
}

int ans = 0;

void calcAns() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int fans = 1e9;
			for (int k = 0; k < 4; k++) {
				chkmin(fans, dp[i][j][k]);
			}
			ans += fans;
		}
	}
}

void run() {
	build();
	calcAns();
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
