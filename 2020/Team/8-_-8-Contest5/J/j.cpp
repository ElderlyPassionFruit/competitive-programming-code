#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD) return a - MOD;
	return a;
}

const int N = 4e3 + 10, M = 1e3 + 10;
int n, m;
bitset<N> used[N];
int dp[2][N];

void Swap() {
	for (int i = 0; i < N; i++) {
		dp[0][i] = dp[1][i];
	}
}

int calc(int val) {
	int ans = 0;
	for (int i = 0; i <= val; i++) {
		ans = add(ans, dp[0][i]);
	}
	return ans;
}

int getVal(int r, int p) {
	int val = 0;
	for (; 2 * (n - r) + 1 >= p; r++) {
		val += 2;
	}
	r--;
	if (2 * (n - r) + 1 != p) val++;
	return val - 1;
}

void wr() {
	cout << "dp = " << endl;
	for (int i = 0; i <= 10; i++) {
		cout << dp[0][i] << " ";
	}
	cout << endl;
}

void calcDp() {
	dp[0][0] = 1;
	//wr();
	for (int i = 2 * n - 1; i >= 1; i--) {
		dp[1][0] = 1;
		for (int myR = 1; 2 * (n - myR) + 1 >= i; myR++) {
			int val = getVal(myR, i);
			//cout << "myR = " << myR << " i = " << i << " val = " << val << endl;
			if (!used[myR][i]) {
				//cout << "calc = " << calc(val - 1) << endl;
				//wr();
				dp[1][val] = add(dp[1][val], calc(val - 1));
			}
		}
		Swap();
		//wr();
	}
}

void makeAns() {
	int ans = 0;
	for (int i = 0; i < N; i++) {
		ans = add(ans, dp[0][i]);
	}
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int r, p;
		cin >> r >> p;
		used[r][p] = 1;
	}

	for (int r = 1; r <= n; r++) {
		for (int p = 1; p <= 2 * (n - r) + 1; p++) {
			cout << getVal(r, p) << " ";
		}
		cout << endl;
	}
	calcDp();
	makeAns();
	return 0;
}