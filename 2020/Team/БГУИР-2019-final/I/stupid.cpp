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
	for (auto &i : a)
		cin >> i;
	int ans = 0;
	for (int l = 0; l < n; l++) {
		set<int> have;
		for (int r = l; r < n; r++) {
			have.insert(a[r]);
			if (have.size() != r - l + 1) continue;
			if (*have.begin() != 1) continue;
			if (*(--have.end()) != r - l + 1) continue;
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}