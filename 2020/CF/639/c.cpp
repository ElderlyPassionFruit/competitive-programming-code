#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int mod(int a, int b) {
	if (a > 0) return a % b;
	a = abs(a);
	if (a % b == 0) return 0;
	return b - a % b;
}

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a) {
		cin >> i;
		i = mod(i, n);
	}
	set<int> have;
	for (int i = -(2 * n) - 100; i < (2 * n) + 100; i++) {
		have.insert(i + a[mod(i, n)]);
	}
	if (have.size() == 2 * n + 100 - (-(2 * n) - 100)) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
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