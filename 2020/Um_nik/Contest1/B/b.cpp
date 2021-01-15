#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 2e3 + 10;
int n, k;
int a[MAXN];

int dp[MAXN];

bool check(int x) {
	for (int i = 0; i < n; i++) {
		dp[i] = i;
		for (int j = 0; j < i; j++) {
			if (abs(a[i] - a[j]) <= (ll)x * (i - j)) {
				dp[i] = min(dp[i], dp[j] + i - j - 1);
			}
		}
		if (dp[i] + n - 1 - i <= k) {
			return true;
		}
	}
	return false;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int l = -1;
	int r = 2e9 + 228;
	while (l < r - 1) {
		int mid = ((ll)l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	cout << r << endl;
	return 0;
}