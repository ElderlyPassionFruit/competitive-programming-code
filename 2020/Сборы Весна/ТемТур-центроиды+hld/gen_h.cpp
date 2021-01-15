#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n = get(3, 30);
	int q = get(1, 10);
	cout << n << " " << q << endl;
	for (int i = 2; i <= n; i++) {
		cout << get(1, i - 1) << " " << get(1, 10) << endl;
	}
	for (int i = 0; i < q; i++) {
		int l = get(1, n);
		int r = get(l, n);
		cout << get(1, n) << " " << l << " " << r << endl;
	}
	return 0;
}