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
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
	int ans = n;
	for (int i = 0; i < n; i++) {
		ans = min(ans, a[i] + n - 1 - i);
	}
	cout << ans << endl;
	return 0;
}