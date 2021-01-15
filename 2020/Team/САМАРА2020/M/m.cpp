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
	int n;
	cin >> n;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int t, d;
		cin >> t >> d;
		ans = max(ans, t) + d;
	}
	cout << ans << endl;
	return 0;
}