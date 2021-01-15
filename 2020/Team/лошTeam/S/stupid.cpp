#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, m;
vector<pair<int, int>> a;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	a.resize(m);
	for (auto &i : a) {
		cin >> i.first >> i.second;
		i.first--;
		i.second--;
	}
	vector<int> order(n);
	iota(all(order), 0);
	do {
		bool ok = true;
		for (auto i : a) {
			ok &= order[i.first] < order[i.second];
		}
		if (ok) {
			for (auto i : order) {
				cout << i + 1 << " ";
			}
			cout << endl;
			return 0;
		}
	} while (next_permutation(all(order)));
	assert(false);
	return 0;
}