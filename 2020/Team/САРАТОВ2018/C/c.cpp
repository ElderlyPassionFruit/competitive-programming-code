#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

void solve() {
	int k, d1, d0;
	cin >> k >> d1  >> d0;
	if (d0 >= d1) {
		cout << "YES\n";
		cout << 1 << " " << d0 - d1 << "\n";
		cout << 2 << " " << d1 << " " << d1 << "\n";
		return;
	}

	if (d1 == 1) {
		cout << "YES\n";
		cout << 1 << " " << d0 + 1 << "\n";
		cout << 1 << " " << k - 1 << "\n";
		return;
	}
	int x = d0 + k + 1 - d1;
	if (x >= k || x < 0) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
	cout << 1 << " " << x << "\n";
	cout << 2 << " " << d1 - 1 << " " << d1 - 1 << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}