#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
vector<int> a;

pair<int, int> get(int pos) {
	int l = pos, r = pos;
	while (l > 0 && r + 1 < n) {
		if (a[l - 1] < a[l] && a[r + 1] < a[r]) {
			l--;
			r++;
		} else {
			break;
		}
	}
	return {l, r};
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
	pair<int, int> ans = {0, 0};
	for (int i = 0; i < n; i++) {
		auto have = get(i);
		if (ans.second - ans.first < have.second - have.first) {
			ans = have;
		}
	}
	cout << ans.first + 1 << " " << ans.second + 1 << endl;
	return 0;
}