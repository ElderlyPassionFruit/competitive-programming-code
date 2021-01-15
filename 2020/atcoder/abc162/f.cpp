#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll
int n;
vector<int> a;
const int MAXN = 2e5 + 10;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int ans;
const int INF = 1e18;
const int MAXLAST = 5;
const int ADD = MAXLAST;
int dp[MAXN][MAXLAST * 2][2];

void run() {
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXLAST * 2; j++)
			for (int k = 0; k < 2; k++)
				dp[i][j][k] = -INF; 
	dp[0][ADD][0] = 0;
	for (int i = 1; i <= n; i++) {
		int now = i / 2;
		int pre = (i - 1) / 2;
		if (now == pre) {
			for (int last = -MAXLAST; last < MAXLAST; last++) {
				int fans = max(dp[i - 1][last + ADD][0], dp[i - 1][last + ADD][1]);
				if (fans == -INF) continue;
				chkmax(dp[i][last + ADD][0], fans);
			}
			for (int last = -MAXLAST; last + 1 < MAXLAST; last++) {
				int fans = dp[i - 1][last + ADD][0];
				if (fans == -INF) continue;
				fans += a[i - 1];
				chkmax(dp[i][last + 1 + ADD][1], fans);
			}
		} else {
			for (int last = -MAXLAST + 1; last < MAXLAST; last++) {
				int fans =  max(dp[i - 1][last + ADD][0], dp[i - 1][last + ADD][1]);
				if (fans == -INF) continue;
				chkmax(dp[i][last - 1 + ADD][0], fans);
			}
			for (int last = -MAXLAST; last < MAXLAST; last++) {
				int fans =  dp[i - 1][last + ADD][0];
				if (fans == -INF) continue;
				fans += a[i - 1];
				chkmax(dp[i][last + ADD][1], fans);
			}
		}
	}
	/*cout << "need = " << endl;
	for (int i = 0; i <= n; i++) {
		cout << i / 2 << " ";
	}
	cout << endl;

	cout << "dp = " << endl;
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i <= n; i++) {
			for (int j = -MAXLAST; j < MAXLAST; j++) {
				cout << dp[i][j + ADD][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}*/
	ans = max(dp[n][ADD][0], dp[n][ADD][1]);
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