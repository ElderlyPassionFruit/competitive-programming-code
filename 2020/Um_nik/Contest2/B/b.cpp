#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 3010;
int n, k;
int p[MAXN];
int dp[MAXN]; // мин. количество ходов чтобы остался ровно суффикс
bool Only[MAXN], Two[MAXN], Can[MAXN];
int mx[MAXN];

bool checkOnly(int pos) {
	if (pos < 0) return false;
	bool ok = false;
	for (int i = pos + 1; i < n; i++) {
		ok |= p[i] >= 0;
	}
	ok &= p[pos] <= 0;
	return ok;
}

bool checkTwo(int pos) {
	if (pos < 0) return false;
	bool ok = false;
	for (int i = pos + 1; i < n; i++) {
		ok |= p[i] >= 0;
	}
	ok &= p[pos] >= 0;
	return ok;
}

bool checkCan(int pos) {
	bool ok = true;
	for (int i = pos + 1; i < n; i++) {
		ok &= p[i] <= 0;
	}
	ok &= p[pos] >= 0;
	return ok;
}

void calcDp() {
	for (int i = n - 1; i >= 0; i--) {
		mx[i] = p[i];
	}
	for (int i = n - 2; i >= 0; i--) {
		mx[i] = max(mx[i], mx[i + 1]);
	}
	for (int i = 0; i < n; i++) {
		Only[i] = checkOnly(i);
		if (i + 1 < n) Two[i] = checkTwo(i);
		if (i + 1 < n) Can[i] = checkCan(i);
	}
	fill(dp, dp + n + 1, MAXN + 1);
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		if (Only[i - 1]) dp[i] = min(dp[i], dp[i - 1] + 1);
		if (Two[i - 2]) dp[i] = min(dp[i], dp[i - 2] + 1);
		if (i < n) {
			for (int j = 0; j < i - 1; j++) {
				if (!Can[j]) continue;
				if (mx[i] == -1) continue;
				dp[i] = min(dp[i], dp[j] + i - j - 1);
			}
		}
		if (p[i - 1] == -1) continue;
		for (int j = 0; j < i - 1; j++) {
			if (!Can[j]) continue;
			dp[i] = min(dp[i], dp[j] + i - j - 1);
		}
	}
}

int ans;

void calcAns() {
	ans = 0;
	for (int i = 0; i <= n; i++) {
		if (dp[i] <= k) ans++;
	}
	cerr << "dp = " << endl;
	for (int i = 0; i <= n; i++) {
		cerr << dp[i] << " ";
	}
	cerr << endl;
	for (int i = 0; i < n - 1; i++) {
		if (dp[i] > k) continue;
		if (!Can[i]) continue;
		ans += min(k - dp[i], n - i - 1);
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x == 0) p[i] = -1;
		else if (x == 100) p[i] = 1;
		else p[i] = 0;
	}
	calcDp();
	calcAns();
	cout << ans << endl;
	return 0;
}