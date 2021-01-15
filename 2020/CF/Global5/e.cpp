#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;

void read() {
	cin >> n;
}

const int MAXN = 1e6 + 10;
int dp[MAXN][2];

const int MOD = 998244353;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int mul(int a, int b) {
	return a * b % MOD;
}

void run() {
	dp[1][1] = 1;
	//dp[2][0] = 1;
	int x = 1;
	for (int i = 2; i <= n; i++) {
		//cout << "x = " << x << endl;
		for (int j = x; j <= i - x - 1; j++) {
			cout << j << " ";
			dp[i][0] = add(dp[i][0], mul(dp[j][1], dp[i - j - 1][0]));
			dp[i][1] = add(dp[i][1], mul(dp[j][0], dp[i - j - 1][1]));
		}
		cout << endl;
		if (x * 4 + 1 == i)
			x *= 2;
	}
	cout << "dp = " << endl;
	for (int i = 1; i <= n; i++) {
		cout << dp[i][0] << " " << dp[i][1] << endl;
	}
}

void write() {
	cout << add(dp[n][0], dp[n][1]) << endl;
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