#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 1e18 + 10;
struct e{
	int c, r, t;
	e() {
		c = 0, r = INF, t = INF;
	}
};

int n, t;
vector <e> a;
void read() {
	cin >> n >> t;
	for (int i = 0; i < n; i++) {
		e help;
		cin >> help.c >> help.r >> help.t;
		a.push_back(help);
	}
}

int ans;
void run() {
	ans = 0;
	vector <int> dp(t + 10, -INF);
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		int cost = a[i - 1].c;
		int must = a[i - 1].t;
		int can = a[i - 1].r;
		vector <int> new_dp(t + 10, -INF);
		for (int j = t; j >= 0; j--) {
			if (j + must <= t)
				new_dp[j + must] = max(new_dp[j + must], dp[j]);
			if (j + must + can <= t)
				new_dp[j + must + can] = max(new_dp[j + must + can], dp[j] + cost);
			if (j + can <= t)
				ans = max(ans, dp[j] + cost);
		}
		dp = new_dp;
		for (auto j : dp)
			ans = max(ans, j);
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}