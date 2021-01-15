#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);

	int w, h, c, p;
	cin >> w >> h >> c >> p;
	set<int> hor = {0};
	set<int> vert = {0, w + 1};
	for (int i = 0; i < p; ++i) {
		string t;
		int j;
		cin >> t >> j;
		if (t == "hor")
			hor.insert(j);
		else
			vert.insert(j);
	}

	std::set<pair<int, int>> v;
	for (int i = 0; i < c; ++i) {
		int x, y;
		cin >> x >> y;
		v.insert({x, y});
	}


	int x, y;
	cin >> x >> y;
	if (hor.count(x - 1)) {
		cout << 0;
		return 0;
	}

	int lv, rv;
	lv = *(--vert.lower_bound(y));
	rv = *vert.lower_bound(y);

	int lcnt = 0, rcnt = 0;
	for (auto p : v) {
		if (p.first == x && lv <= p.second && p.second <= y)
			++lcnt;
		if (p.first == x && y <= p.second && p.second <= rv)
			++rcnt;
	}

	cout << min(lcnt, rcnt);

	return 0;
}