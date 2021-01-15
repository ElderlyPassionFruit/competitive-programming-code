#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ll x, y;
	cin >> x >> y;
	if (min(x, y) == 0) {
		cout << max(x, y) << endl;
		return 0;
	}
	cout << min(x, y) << endl;
	return 0;
}