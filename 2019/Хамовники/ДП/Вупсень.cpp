#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MAXN = 710;
int dp[MAXN][MAXN][MAXN / 2];
char a[MAXN], b[MAXN];
int n, m;
void read() {
	string s;
	cin >> s;
	n = s.length();
	for (int i = 0; i < n; i++)
		a[i + 1] = s[i];
	cin >> s;
	m = s.length();
	for (int i = 0; i < m; i++)
		b[i + 1] = s[i];
}
string ans;
void run() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k < MAXN / 2; k++) {
				dp[i][j][k] = max(dp[i - 1][j][k], dp[i][j - 1][k]);
				if (a[i] == b[j]) {
					if (a[i] == '(') {
						dp[i][j][k + 1] = max(dp[i][j][k + 1], dp[i - 1][j - 1][k] + 1);
					}
					else {
						if (dp[i - 1][j - 1][k + 1] == 0)
							continue;
						dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k + 1] + 1);
					}
				}
			}
		}
	}

	int fans= 0;
	for (int i = 0; i <= MAXN / 2; i++)
		fans = max(fans, dp[n][m][i]);
	cout << fans << endl;
}

void write() {
	
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