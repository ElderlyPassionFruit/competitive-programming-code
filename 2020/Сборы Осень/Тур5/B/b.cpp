#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

	
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1010;
int dp[MAXN][MAXN];
int help_odd[MAXN], help_even[MAXN];
int help[MAXN];
int n, k;
int a[MAXN];

void read() {
	cin >> n >> k;
	for (int i = 1; i <= k; i++)
		cin >> a[i];
}

const int INF = -1e18;
int ans;

void run() {
	sort(a + 1, a + k + 1);
	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXN; j++){
			help_odd[i] = INF;
			help_even[i] = INF;
			dp[i][j] = INF;
		}

	deque<pair<int, int> > q;

	for (int i = 1; i <= k; i++) {
		dp[i][1] = (a[i] - 1) / 2;
		for (int j = 2; j <= i; j++) {
			if (a[i] % 2 == 1) {
				dp[i][j] = max(dp[i][j], help_odd[j - 1] + a[i] / 2 - 1);
				dp[i][j] = max(dp[i][j], help_even[j - 1] + a[i] / 2 - 1);
			}
			else {
				dp[i][j] = max(dp[i][j], help_odd[j - 1] + a[i] / 2 - 2);
				dp[i][j] = max(dp[i][j], help_even[j - 1] + a[i] / 2 - 1);
			}
		}
		q.push_back({a[i], i});
		while (!q.empty() && q[0].first + 1 < a[i + 1]) {
			int x = q[0].first;
			int pos = q[0].second;
			q.pop_front();
			for (int j = 1; j <= pos; j++) {
				if (x % 2 == 0)
					help_even[j] = max(help_even[j], dp[pos][j] - x / 2);
				else 
					help_odd[j] = max(help_odd[j], dp[pos][j] - x / 2);
			}
		}
	}

	ans = k;
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= i; j++) {
			int have_place = dp[i][j] + (n - a[i]) / 2;
			if (have_place >= k - j)
				chkmin(ans, k - j);
		}
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