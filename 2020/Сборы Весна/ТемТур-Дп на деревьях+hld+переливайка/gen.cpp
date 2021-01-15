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
	int n = get(5, 100);
	cout << n << " " << get(1, n - 1) << endl;
	for (int i = 2; i <= n; i++) {
		cout << get(1, i - 1) << " " << i << endl;
	}
	return 0;
}