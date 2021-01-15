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
	a %= MOD;
	b %= MOD;
	return (a + b) % MOD;
	a += b;
	if (a >= MOD) return a - MOD;
	return a;
}

int n, x;

void read() {
	cin >> n >> x;
}

const int N = 540;

int dp[2][N][N];
int pref[N][N];

int get(int myX, int r) {
	if (myX >= N) return 0;
	int ans = 0;
	/*for (int i = 0; i <= r; i++) {
		ans = add(ans, dp[0][myX][i]);
	}*/
	ans = pref[myX][r];
	return ans;
}

void Swap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dp[0][i][j] = dp[1][i][j];
			pref[i][j] = dp[0][i][j];
			if (j > 0) pref[i][j] = add(pref[i][j], pref[i][j - 1]);
		}
	}
}

void calcDp() {
	for (int it = 0; it < 2; it++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				dp[it][i][j] = 0;
			}
		}
	}
	dp[1][0][0] = 1;
	Swap();
	for (int i = 1; i <= n; i++) {
		for (int myX = 0; myX < N; myX++) {
			for (int num = 0; num <= x; num++) {
				dp[1][myX][num] = get(myX ^ num, num);
			}
		}
		/*cout << "dp = " << endl;
		for (int i = 0; i <= x; i++) {
			for (int j = 0; j <= x; j++) {
				cout << dp[1][i][j] << " ";
			}
			cout << endl;
		}*/
		Swap();
	}
}

int ans;

void makeAns() {
	ans = get(x, x);
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