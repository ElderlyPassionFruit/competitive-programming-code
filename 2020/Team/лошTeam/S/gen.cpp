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

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n = get(2, 2);
	int m = get(1, 4);
	vector<pair<int, int>> ed;
	for (int i = 0; i < m; i++) {
		int l = get(1, n - 1);
		int r = get(l + 1, n);
		ed.push_back({l, r});
	}
	sort(all(ed));
	ed.resize(unique(all(ed)) - ed.begin());
	m = ed.size();
	cout << n << " " << m << endl;
	vector<int> p(n);
	iota(all(p), 0);
	shuffle(all(p), rnd);
	for (auto i : ed) {
		cout << p[i.first - 1] + 1 << " " << p[i.second - 1] + 1 << endl;
	}
	return 0;
}