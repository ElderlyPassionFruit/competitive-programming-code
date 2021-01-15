#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
string s;

void read() {
	cin >> n;
	cin >> s;
}

const int MAXN = 1e5 + 10;
ll dp[2][MAXN][3];
string let = "JOI";

void build_dp() {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			dp[0][i][j] = dp[0][i - 1][j];
			if (let[j] != s[i - 1]) continue;
			if (j == 0) 
				dp[0][i][j]++;
			else
				dp[0][i][j] += dp[0][i - 1][j - 1];
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < 3; j++) {
			dp[1][i][j] = dp[1][i + 1][j];
			if (let[j] != s[i - 1]) continue;
			if (j == 2)
				dp[1][i][j]++;
			else
				dp[1][i][j] += dp[1][i + 1][j + 1];
		}
	}
}

ll ans;

ll fdp[2][3];

ll calc_pos(int i, int j) {
	for (int i = 0; i < 2; i++) for (int j = 0; j < 3; j++) fdp[i][j] = 0;
	if (i > 0) {
		for (int pos = 0; pos < 3; pos++){
			fdp[0][pos]	= dp[0][i - 1][pos];
			if (j != pos) continue;
			if (j == 0)
				fdp[0][pos]++;
			else
				fdp[0][pos] += dp[0][i - 1][pos - 1];
		}
	}
	else {
		if (j == 0)
			fdp[0][0] = 1;
	}
	if (i < n + 1) {
		for (int pos = 0; pos < 3; pos++) {
			fdp[1][pos] = dp[1][i][pos];
		}
	}

	/*cout << "fdp = " << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			cout << fdp[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	ll ans = fdp[0][2] + fdp[1][0];
	ans += fdp[0][0] * fdp[1][1];
	ans += fdp[0][1] * fdp[1][2];
	return ans;
}

void calc_ans() {
	ans = 0;
	//calc_pos(4, 1);
	//return;
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j < 3; j++) {
			chkmax(ans, calc_pos(i, j));
		}
	}
}

void run() {
	build_dp();
	/*cout << "dp = " << endl;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			cout << dp[0][i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			cout << dp[1][i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
	calc_ans();
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