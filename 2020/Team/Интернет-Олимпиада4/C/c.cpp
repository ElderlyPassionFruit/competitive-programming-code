#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e4 + 10;
map<int, int> dp[MAXN];
int arr[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, a, b;
	cin >> n >> a >> b;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	dp[1][arr[1]] = 1;
	dp[1][-arr[1]] = 0;
	for (int i = 2; i <= n; i++) {
		for (int j = a; j <= b; j++) {
			if (j - arr[i] >= a) {
				if (dp[i - 1].count(j - arr[i])) {
					dp[i][j] = 1;
					continue;
				}
			}
			if (j + arr[i] <= b) {
				if (dp[i - 1].count(j + arr[i])) {
					dp[i][j] = 0;
					continue;
				}
			}
		}
	}
	if (dp[n].empty()) {
		cout << "Impossible" << endl;
		exit(0);
	}
	string ans = "";
	int now = dp[n].begin()->first;
	
	for (int i = n; i >= 1; i--) {
		assert(dp[i].count(now));
		if (dp[i][now]) {
			ans += "1";
			now -= arr[i];
		}
		else {
			ans += "0";
			now += arr[i];
		}
	}
	reverse(all(ans));
	cout << ans << endl;
	return 0;
}