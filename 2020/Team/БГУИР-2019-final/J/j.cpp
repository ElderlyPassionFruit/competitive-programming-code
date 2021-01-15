#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;

bool check(int x, int y) {
	if (x == 0 && y == 0) return false;
	while (y < n) {
		int nxt = x + y;
		x = y;
		y = nxt;
	}
	return y == n;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	vector<pair<int, int>> ans;
	ans.push_back({0, n});
	for (int x = 0; x <= n / 2; x++) {
		int cnt0x = 0;
		int cnt0y = 1;
		int cnt1x = 1;
		int cnt1y = 1;
		while (cnt1x * x <= n && cnt1y <= n) {
			int have = n - cnt1x * x;
			if (have % cnt1y == 0) {
				int y = have / cnt1y;
				ans.push_back({x, y});
			}
			int nxt;
			nxt = cnt0x + cnt1x;
			cnt0x = cnt1x;
			cnt1x = nxt;

			nxt = cnt0y + cnt1y;
			cnt0y = cnt1y;
			cnt1y = nxt;
		}
	}
	sort(all(ans), [&] (pair<int, int> i, pair<int, int> j) {
		if (i.first + i.second != j.first + j.second)
			return i.first + i.second < j.first + j.second;
		return i.first < j.first;
	});
	assert(ans.size());
	cout << ans[0].first << " " << ans[0].second << endl;
	return 0;
}