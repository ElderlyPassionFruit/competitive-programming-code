#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

#define int ll

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("sochi.in", "r", stdin);
	freopen("sochi.out", "w", stdout);
	int n, d;
	cin >> n >> d;
	vector<int> a;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
	int ans = a.back();
	a.pop_back();
	int sum = 0;
	int cnt = 0;
	while (!a.empty() && a.back() >= 3 * d) {
		sum += a.back();
		cnt++;
		a.pop_back();
	}

	ans += sum - 2 * cnt * d;
	int sz = a.size();
	if (ans < 3 * d)
		sz = min(sz, 1LL);

	for (int i = 0; i < min(sz, 2LL); i++) {
		if (a.back() >= 2 * d) {
			ans += a.back() - 2 * d;
			a.pop_back();
		}
	}
	cout << ans;
	return 0;
}