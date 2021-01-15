#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	vector<int> a(4);
	for (auto &i : a)
		cin >> i;
	int t;
	cin >> t;
	sort(all(a));
	if (t == 1) {
		if (a[3] >= a[0] + a[1] + a[2]) {
			cout << 0;
		} else {
			cout << 1;
		}
	} else if (t == 2) {
		if (a[3] >= a[0] + a[1] + a[2]) {
			cout << 0;
			return 0;
		}
		if (a[3] == a[0] || a[4] == a[1]) {
			cout << 0;
			return 0;
		}
		cout << 1;
	} else if (t == 3) {
		if (a[0] == a[1] && a[2] == a[3]) {
			cout << 1;
		} else {
			cout << 0;
		}
	} else {
		if (a[0] == a[3]) {
			cout << 1;
		} else {
			cout << 0;
		}
	}
	return 0;
}