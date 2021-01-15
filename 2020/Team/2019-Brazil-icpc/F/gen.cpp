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
	int n = 10000;
	cout << n << endl;
	int x1 = 0, y1 = 0, x2 = 100000, y2 = 100000;
	for (int i = 0; i < n; i++) {
		cout << get(x1, x2) << " " << get(y1, y2) << " " << get(x1, x2) << get(y1, y2) << endl; 
	}
	cout << get(1, 100) << endl;
	cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
}