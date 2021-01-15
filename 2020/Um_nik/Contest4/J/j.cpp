#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	ll ans = 0;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if (x == 0) {
			ans += cnt;
		} else {
			cnt++;
		}
	}
	cout << ans << endl;
	return 0;
}