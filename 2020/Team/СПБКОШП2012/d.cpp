#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("frog.in", "r", stdin);
	freopen("frog.out", "w", stdout);
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
	reverse(all(a));
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] - i <= 0) break;
		int j = i + 1;
		while (j < n && a[j] == a[i])
			j++;
		ans += (ll) (j - i) * (a[i] - i);
		i = j - 1;
	}
	cout << ans;
	return 0;
}