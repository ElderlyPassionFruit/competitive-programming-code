#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int sum;
	cin >> sum;
	vector<int> cost(9);
	for (auto &i : cost) {
		cin >> i;
	}
	int mn = *min_element(all(cost));
	int len = sum / mn;
	if (len == 0) {
		cout << -1 << endl;
		return 0;
	}
	string ans = "";
	for (int pos = 0; pos < len; pos++) {
		for (int j = 8; j >= 0; j--) {
			if (sum >= cost[j] && (sum - cost[j]) / mn >= len - pos - 1) {
				ans += '0' + 1 + j;
				sum -= cost[j];
				break;
			}
		}
	}
	cout << ans << endl;
	return 0;
}