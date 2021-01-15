#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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
	int n = get(2, 4);
	int m = get(1, 10);
	cout << n << " " << m << endl;
	for (int i = 0; i < m; i++) {
		int u = get(1, n);
		int v = get(1, n);
		while (v == u) v = get(1, n);
		int c = 0;
		int d = get(1, 2);
		cout << u << " " << v << " " << c << " " << d << endl;
	}
	return 0;
}