#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 1e3 + 10;
int n;
int a[MAXN][MAXN][2];

int dp[MAXN][MAXN];
int par[MAXN][MAXN];

int solve(int ind) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = 0;
			par[i][j] = -1;
		}
	}
	dp[0][0] = a[0][0][ind];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == 0 && j == 0) continue;
			dp[i][j] = 1e9;
			if (i > 0 && dp[i][j] > dp[i - 1][j]) {
				dp[i][j] = dp[i - 1][j];
				par[i][j] = 0;
			}
			if (j > 0 && dp[i][j] > dp[i][j - 1]) {
				dp[i][j] = dp[i][j - 1];
				par[i][j] = 1;
			}
			dp[i][j] += a[i][j][ind];
		}
	}
	return dp[n - 1][n - 1];
}

void getPar(int ind) {
	solve(ind);
	string ans = "";
	int i = n - 1, j = n - 1;
	while (par[i][j] != -1) {
		if (par[i][j] == 0) {
			i--;
			ans += 'D';
		} else {
			j--;
			ans += 'R';
		}
	}
	cout << dp[n - 1][n - 1] << endl;
	reverse(all(ans));
	cout << ans << endl;
	exit(0);
}

void outZero(int i) {
	cout << 1 << endl;
	string ans = "";
	for (int x = 0; x < i; x++) {
		ans += "D";
	}
	for (int i = 0; i < n - 1; i++) {
		ans += "R";
	}
	for (int x = i; x < n - 1; x++) {
		ans += "D";
	}
	cout << ans << endl;
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	int I = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int x;
			cin >> x;
			while (x > 0 && x % 2 == 0) {
				a[i][j][0]++;
				x /= 2;
			}
			while (x > 0 && x % 5 == 0) {
				a[i][j][1]++;
				x /= 5;
			}
			if (x == 0) {
				I = i, a[i][j][0] = a[i][j][1] = 1e9;
			}
		}
	}

	int ans0 = solve(0), ans1 = solve(1);

	if (I != -1 && min(ans0, ans1) > 1) {
		outZero(I);
	} else if (ans0 <= ans1) {
		getPar(0);
	} else {
		getPar(1);
	}
	return 0;
}