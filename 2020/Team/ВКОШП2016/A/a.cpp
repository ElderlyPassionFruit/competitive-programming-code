#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int a, b, c;
	cin >> a >> b >> c;
	if (a + b == c || a + c == b || c + b == a) {
		cout << 0;
		return 0;
	}
	for (int i = 1; i < c; i++) {
		if (a + i == b + c - i) {
			cout << 3 << endl;
			cout << i << " " << c - i << endl;
			return 0;
		}
	}
	for (int i = 1; i < b; i++) {
		if (a + i == b + c - i) {
			cout << 2 << endl;
			cout << i << " " << b - i << endl;
			return 0;
		}
	}
	for (int i = 1; i < a; i++) {
		if (b + i == a + c - i) {
			cout << 1 << endl;
			cout << i << " " << a - i << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;
}