#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int get(int x) {
	int ans = 0;
	while (x % 2 == 0) {
		ans += x / 2;
		x /= 2;
	}
	ans += x * (x - 1) / 2;
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> ans;
	for (int x = 1; x <= 1e6; x++) {
		if (get(x) == n) {
			ans.push_back(x);
		}
	}
	if (ans.size() == 0) ans.push_back(-1);
	for (auto i : ans) {
		cout << i << endl;
	}
	return 0;
}