#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 12;

int n, m, x;
int c[MAXN], a[MAXN][MAXN];

void read() {
	cin >> n >> m >> x;
	for (int i = 0; i < n; i++) {
		cin >> c[i];
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
}

int have[MAXN];

bool check(int mask) {
	fill(have, have + m, 0);
	for (int i = 0; i < n; i++) {
		if (!((mask >> i) & 1)) continue;
		for (int j = 0; j < m; j++) {
			have[j] += a[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		if (have[i] < x) return false;
	}
	return true;
}

int cost(int mask) {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			ans += c[i];
		}
	}
	return ans;
}

const int INF = 1e9 + 10;
int ans;

void run() {
	ans = INF;
	for (int mask = 0; mask < (1 << n); mask++) {
		if (!check(mask)) continue;
		chkmin(ans, cost(mask));
	}
	if (ans == INF) ans = -1;
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