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
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	int r = a[0] + a[1] - 1;
	int l = a[n - 1] - a[0] + 1;
	if (l <= r) {
		cout << "YES" << "\n" << l << endl;
	}
	else {
		cout << "NO" << endl;
	}
	return 0;
}