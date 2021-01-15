#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 1010;
const int MOD = 1e9 + 7;

int n, m, k;
int a[MAXN][MAXN];
void read() {
	cin >> n >> m >> k;
}

void run() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			a[i][j] = (i - 1) * m + j;
			a[i][j] %= MOD;
		}
	}
	while (k--) {
		char type;
		int x, y;
		cin >> type >> x >> y;
		if (type == 'R') {
			for (int j = 1; j <= m; j++) {
				a[x][j] *= y;
				a[x][j] %= MOD;
			} 
		} else {
			for (int i = 1; i <= n; i++) {
				a[i][x] *= y;
				a[i][x] %= MOD;
			}
		}
	}
}

void write() {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans += a[i][j];
			ans %= MOD;
		}
	}
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