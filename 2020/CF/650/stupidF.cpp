#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

bool check(int mask) {
	vector<int> have;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			have.push_back(a[i]);
		}
	}
	vector<int> b = have;
	sort(all(b));
	if (b != have) return false;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) continue;
		if (a[i] > have[0] && a[i] < have.back()) {
			return false;
		}
	}
	return true;
}

int get(int mask) {
	return __builtin_popcount(mask);
}

void solve() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}

	int ans = n;
	for (int mask = 1; mask < (1 << n); mask++) {
		if (check(mask)) {
			chkmin(ans, n - get(mask));
		}
	}
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}