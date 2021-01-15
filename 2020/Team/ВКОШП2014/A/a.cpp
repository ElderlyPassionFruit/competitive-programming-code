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
	freopen("chaos.in", "r", stdin);
	freopen("chaos.out", "w", stdout);
	int a, b, c, d, k;
	cin >> a >> b >> c >> d >> k;
	for (int i = 0; i < k; i++) {
		int last = a;
		a *= b;
		a -= c;
		a = max(a, 0LL);
		a = min(a, d);
		if (a == last) {
			cout << a << endl;
			return 0;
		}
		if (a == d) {
			cout << d << endl;
			return 0;
		}
		if (a == 0) {
			cout << 0 << endl;
			return 0;
		}
	}
	cout << a << endl;
	return 0;
}