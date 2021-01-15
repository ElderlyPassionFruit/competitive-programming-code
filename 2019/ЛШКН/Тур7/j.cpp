#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e6 + 10;

int prime[MAXN];
int dp[MAXN];

int t, l, r;

void read() {
	cin >> t >> l >> r;
}

const int MOD = 1e9 + 7;
const int INF = 1e18 + 10;

void build() {
	vector<int> pr;
 
	for (int i = 2; i <= MAXN; i++) {
		if (prime[i] == 0) {
			prime[i] = i;
			pr.push_back (i);
		}
		for (int j = 0; j < pr.size() && pr[j] <= prime[i] && i * pr[j] < MAXN; j++)
			prime[i * pr[j]] = pr[j];
	}
	
	dp[1] = 0;
	for (int i = 2; i <= r; i++) {
		dp[i] = INF;
		for (int j = i; j > 1; j = j / prime[j]) {
			chkmin(dp[i], dp[i / prime[j]] + i * (prime[j] - 1) / 2);
		}
		dp[i] %= MOD;
	}
	//cout << "dp = " << endl;
	//for (int i = 0; i <= r; i++)
	//	cout << dp[i] << " ";
	//cout << endl;
}

int ans = 0;

void run() {
	build();
	int have = 1;
	for (int i = l; i <= r; i++) {
		ans += dp[i] * have;
		ans %= MOD;
		have *= t;
		have %= MOD;
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