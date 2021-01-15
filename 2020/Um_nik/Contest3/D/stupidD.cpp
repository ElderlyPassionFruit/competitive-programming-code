#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i];
	}
	int ans = 1e9 + 228 + 1337;
	for (int mask = 0; mask < (1 << (n * m)); mask++) {
		int fans = 0;
		int bal = 0;
		bool ok = true;
		for (int bit = 0; bit < (n * m); bit++) {
			if ((mask >> bit) & 1) {
				bal--;
				fans += b[bit % n];
			} else {
				bal++;
				fans += a[bit % n];
			}
			ok &= bal >= 0;
		}
		ok &= bal == 0;
		if (!ok) continue;
		ans = min(ans, fans);
	}
	cout << ans << endl;
	return 0;
}