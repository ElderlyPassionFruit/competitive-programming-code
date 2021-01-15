#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int n, c, t;
vector<int> a;

bool check(int cnt) {
	int now = 0;
	int have = 1;
	for (auto i : a) {
		if (i > cnt * t) return false;
		if (now + i <= cnt * t) {
			now += i;
		} else {
			now = i;
			have++;
		}
	}
	return have <= c;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> c >> t;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
	int l = 0, r = 1e9 + 228;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	cout << r << endl;
	return 0;
}