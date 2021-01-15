#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a) {
		cin >> i;
	}
	auto have = a;
	sort(all(have));
	if (a == have) {
		cout << 0 << endl;
		return;
	}
	vector<int> x;
	for (int i = 0; i < n; i++) {
		if (a[i] - 1 == i) continue;
		x.push_back(i);
	}
	sort(all(x));
	if (x.empty() || x.back() - x[0] + 1 == (int)x.size()) {
		cout << 1 << endl;
	} else {
		cout << 2 << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}