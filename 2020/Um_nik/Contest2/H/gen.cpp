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
	int a = get(0, 5);
	cout << a << endl;
	int n = get(1, 10);
	for (int i = 0; i < n; i++) {
		cout << get(0, 9);
	}
	cout << endl;
	return 0;
}