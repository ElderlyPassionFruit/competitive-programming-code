#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

int mx = 10;

set<pair<int, int>> used;

pair<int, int> gen() {
	while (true) {
		int x = get(-mx, mx);
		if (x == 0) continue;
		int y = get(1, mx);
		ll g = __gcd(abs(x), abs(y));
		x /= g;
		y /= g;
		if (used.count({x, y})) continue;
		used.insert({x, y});
		return {x, y};
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	used.insert({0, 0});
	int n = get(1, 20);
	cout << n << endl;

	for (int i = 0; i < n; i++) {
		pair<int,int> have;
		have = gen();
		cout << have.first << " " << have.second << " ";
		have = gen();
		cout << have.first << " " << have.second << endl;
	}
	return 0;
}