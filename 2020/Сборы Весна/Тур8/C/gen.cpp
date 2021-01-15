#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int a, b, c;
	a = get(1, 10);
	b = get(0, 10);
	c = get(0, a);
	cout << a << " " << b << " " << c << endl;
	char last = '+';
	for (int i = 0; i < a; i++) {
		if (get(1, 3) == 1 && last != '+' && i != a - 1) {
			cout << '+';
			last = '+';
		} else {
			last = 'x';
			cout << get(1, 9);
		}
	}
	cout << endl;
	return 0;
}