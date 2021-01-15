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
	int ans1 = 0, ans2 = 0;
	cin >> n;
	vector<int> a;
	for (int i = 0; i < n; i++) {
		int sz;
		cin >> sz;
		for (int j = 0; j < sz / 2; j++) {
			int x;
			cin >> x;
			ans1 += x;
		}
		if (sz & 1) {
			int x;
			cin >> x;
			a.push_back(x);
		}
		for (int j = 0; j < sz / 2; j++) {
			int x;
			cin >> x;
			ans2 += x;
		}
	}
	sort(all(a));
	reverse(all(a));
	for (int i = 0; i < (int)a.size(); i++) {
		if (i & 1) ans2 += a[i];
		else ans1 += a[i];
	}
	cout << ans1 << " " << ans2 << endl;
	return 0;
}