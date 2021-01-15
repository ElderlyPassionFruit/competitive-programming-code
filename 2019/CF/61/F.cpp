#include <bits/stdc++.h>

using namespace std;
#define int long long


int n;
string s, t;
void read() {
	cin >> n;
	cin >> s;
	t = s[0];
	for (int i = 1; i < n; i++)
		if (s[i] != t.back())
			t += s[i];
}

const int MAXN = 510;
int dp[MAXN][MAXN];

void run() {
	cout << t << endl;
	for (int i = 1; i <= n; i++) {
		dp[i][i] = 1;
		for (int j = i - 1; j >= 1; j--) {
			dp[j][i] = i - j + 1;
			for (int k = j; k < i; k++) {
				dp[j][i] = min(dp[j][i], dp[j][k] + dp[k + 1][i]);
			} 

			for (int k = j; k < i; k++) {
				for (int t = k + 1; t <= i; t++) {
					if (s[k - 1] == s[t - 1]) {
						dp[j][i] = min(dp[j][i], dp[j][k - 1] + dp[k + 1][t - 1] + dp[t][i] + 1);
					} 
				}
			}
		}
	}
}

void write() {
	cout << dp[1][n] << endl;
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