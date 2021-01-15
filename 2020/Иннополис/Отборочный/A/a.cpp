#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ll a, b, x;
	cin >> a >> b >> x;
	ll ans = 0;
	for (int i = 0; i * a <= 1000; i++) {
		for (int j = 0; i * a + j * b <= 1000; j++) {
			if (i + j == 0) continue;
			if (a * i * 100 == (a * i + b * j) * x)
				ans = max(ans, a * i + b * j);
		}
	}
	cout << ans << endl;
	return 0;
}