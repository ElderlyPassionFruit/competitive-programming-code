#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
const int INF = 1e18 + 10
int dp[MAXN][3];

int n;
int table[MAXN][3];

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> table[i][j];
		}
	}
}

int ans;

void run() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < 3; j++)
			dp[i][j] = -INF;
	dp[1][0] = table[1][0];

	for (int i = 1; i <= n; i++) {
		
	}

	ans = dp[n][2];
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