#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<int> a;

bool check(int mask, int k) {
	int val = 0, len = 0;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) continue;
		if (val >= a[i] && len < k) return false;
		if (val >= a[i]) {
			len = 1;
		} else {
			len++;
		}
		val = a[i];
	}
	if (len != 0 && len < k) return false;
	return true;
}

int get(int mask) {
	return __builtin_popcount(mask);
}

void solve(int k) {
	int ans = 0;
	for(int mask = 0; mask < (1 << n); mask++) {
		if (check(mask, k)) {
			ans = max(ans, n - get(mask));
		}
	}
	cout << ans << " ";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++) {
		solve(i);
	}
	cout << endl;
	return 0;
}