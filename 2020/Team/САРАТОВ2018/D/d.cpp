#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while (t--) {
		ll x;
		cin >> x;
		ll l = 0, r = 2e9 + 100;
		while (l < r - 1) {
			ll mid = (l + r) / 2;
			if (mid * (mid + 1) / 2 <= x)
				l = mid;
			else
				r = mid;
		}
		if (l <= 2)
			cout << 0 << "\n";
		else
			cout << l * (l + 1) / 2 << "\n"; 
	}
	return 0;
}