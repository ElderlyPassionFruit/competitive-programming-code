#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int MOD = 998244353;

int add(int a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0) a += MOD;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

const int N = 1e3 + 10;
int n, m;
int a[N], b[N];

void read() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
	}
}

int dp[N][N];
int pref[N][N];

void upd(int x, int y) {
	pref[x][y] = dp[x][y];
	if (x - 1 >= 0)
	pref[x][y] = add(pref[x][y], pref[x - 1][y]);
	if (y - 1 >= 0)
	pref[x][y] = add(pref[x][y], pref[x][y - 1]);
	if (x - 1 >= 0 && y - 1 >= 0)
	pref[x][y] = sub(pref[x][y], pref[x - 1][y - 1]);
}

int calc(int x, int y) {
	return pref[x][y];
	/*int ans = 0;
	for (int i = 0; i <= x; i++) {
		for (int j = 0; j <= y; j++) {
			ans = add(ans, dp[i][j]);
		}
	}
	return ans;*/
}


void calcDp() {
	dp[0][0] = 1;
	upd(0, 0);
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i > 0 && j > 0 && a[i] == b[j]) {
				dp[i][j] = calc(i - 1, j - 1);
			}
			upd(i, j);
		}
	}
}

int ans;

void makeAns() {
	ans = sub(calc(n, m), 1);
	//ans = calc(n, m);
}

void run() {
	calcDp();
	makeAns();
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}