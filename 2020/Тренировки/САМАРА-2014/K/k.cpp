#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
int n, m;
vector<int> a, b;
vector<int> d, t;

void chkmax(int & x, const int & y) {
	x = max(x, y);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a.resize(n), b.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
	for (auto &i : b) {
		cin >> i;
	}
	for (int i = 1; i < n; i++) {
		chkmax(a[i], a[i - 1]);
		chkmax(b[i], b[i - 1]);
	}
	cin >> m;
	d.resize(m), t.resize(m);
	for (auto &i : d) {
		cin >> i;
	}
	for (auto &i : t) {
		cin >> i;
	}
	for (int i = 0; i < m; i++) {
		int A = upper_bound(all(a), d[i]) - a.begin();
		int B = upper_bound(all(b), t[i]) - b.begin();
		if (A > B) {
			cout << "Constantine" << "\n";
		} else if (A < B) {
			cout << "Mike" << "\n";
		} else {
			cout << "Draw" << "\n";
		}
	}
	return 0;
}