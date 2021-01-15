#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int n, t;
vector<pair <int, int> > a;
const int MOD = 1e9 + 7;

void read() {
	cin >> n >> t;
	a.resize(n);
	for (auto &i : a)
		cin >> i.first >> i.second;
}

const int MAXN = 20;
int dp[MAXN][MAXN][MAXN][3];
int fact[MAXN];

void calc() {
	dp[1][0][0][0] = 1;
	dp[0][1][0][1] = 1;
	dp[0][0][1][2] = 1;

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			for (int k = 0; k < MAXN; k++) {
				if (i == 0 && j == 0 && k == 0) continue;
				if (i > 0) {
					dp[i][j][k][0] += dp[i - 1][j][k][1] + dp[i - 1][j][k][2];
					dp[i][j][k][0] %= MOD;
				}
				if (j > 0) {
					dp[i][j][k][1] += dp[i][j - 1][k][0] + dp[i][j - 1][k][2];
					dp[i][j][k][1] %= MOD;
				}
				if (k > 0) {
					dp[i][j][k][2] += dp[i][j][k - 1][0] + dp[i][j][k - 1][1];	
					dp[i][j][k][2] %= MOD;
				}
			}
		}
	}
	fact[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
}

bool check(vector<int> & help) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (help[i]) {
			sum += a[i].first;
		}
	}
	return sum == t;
}

int cnt(vector<int> & help) {
	int cnt1 = 0, cnt2 = 0, cnt3 = 0;
	for (int i = 0; i < n; i++) {
		if (help[i]) {
			if (a[i].second == 1)
				cnt1++;
			if (a[i].second == 2)
				cnt2++;
			if (a[i].second == 3)
				cnt3++;
		}
	}
	int fans = 0; 
	if (cnt1 > 0) {
		fans += dp[cnt1][cnt2][cnt3][0];
		fans %= MOD;
	}
	if (cnt2 > 0) {
		fans += dp[cnt1][cnt2][cnt3][1];
		fans %= MOD;
	}
	if (cnt3 > 0) {
		fans += dp[cnt1][cnt2][cnt3][2];
		fans %= MOD;
	}
	fans = fans * fact[cnt1] % MOD * fact[cnt2] % MOD * fact[cnt3] % MOD;
	return fans;
}

int ans = 0;
void run() {
	calc();
	
	for (int i = 1; i <= n; i++) {
		vector<int> help(n, 0);
		for (int j = 0; j < i; j++)
			help[n - 1 - j] = 1;
		do {
			if (check(help)) {
				ans += cnt(help);
				ans %= MOD;
			}
		} while (next_permutation(help.begin(), help.end()));
	}
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