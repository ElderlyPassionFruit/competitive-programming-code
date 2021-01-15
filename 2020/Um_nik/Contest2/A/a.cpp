#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
bool check(int nums, int len) {
	if (nums % 2 == 1) {
		return nums * (nums - 1) / 2 + 1 <= len;
	} else {
		return nums * (nums - 1) / 2 + nums / 2 <= len;
	}
}

int get(int n, int m) {
	int l = 0, r = m + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid, n)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	return l;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m;
	cin >> n >> m;
	n = get(n, m);
	vector<int> a(m);
	for (int i = 0; i < m; i++) {
		cin >> a[i];
		cin >> a[i];
	}
	sort(all(a));
	reverse(all(a));
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		ans += a[i];
	}
	cout << ans << endl;
	return 0;
}