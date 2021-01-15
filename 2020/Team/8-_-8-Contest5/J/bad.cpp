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

const int N = 4e3 + 10;
int n, m;
bitset<N> used[N];
int dp[2][N];
int pref[N];

void Swap() {
	for (int i = 0; i < N; i++) {
		dp[0][i] = dp[1][i];
		pref[i] = dp[0][i];
		if (i > 0) {
			pref[i] = add(pref[i], pref[i - 1]);
		} 
	}
}

int calc(int val) {
	if (val < 0) return 0;
	return pref[val];
}

int getVal(int r, int p) {
	int val = 0;
	//for (; 2 * (n - r) + 1 >= p; r++) {
	//	val += 2;
	//}
	int x = (2 * n - p + 1) / 2;
	int d = x - r;
	val += 2 * d;
	r = x;
	if (2 * (n - r) + 1 != p) val++;
	return val + 1;
}

void wr() {
	cout << "dp = " << endl;
	for (int i = 0; i <= 10; i++) {
		cout << dp[0][i] << " ";
	}
	cout << endl;
}

void calcDp() {
	dp[1][0] = 1;
	Swap();
	for (int i = 2 * n - 1; i >= 1; i--) {
		for (int myR = 1; 2 * (n - myR) + 1 >= i; myR++) {
			int val = getVal(myR, i);
			if (!used[myR][i]) {
				dp[1][val] = add(dp[1][val], calc(val - 1));
			}
		}
		Swap();
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
	freopen("operators.in", "r", stdin);
	freopen("operators.out", "w", stdout);
	
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int r, p;
		cin >> r >> p;
		used[r][p] = 1;
	}
	/*	for (int r = 1; r <= n; r++) {
		for (int p = 1; p <= 2 * (n - r) + 1; p++) {
			cout << getVal(r, p) << " ";
		}
		cout << endl;
	}*/
	calcDp();
	makeAns();
	return 0;
}