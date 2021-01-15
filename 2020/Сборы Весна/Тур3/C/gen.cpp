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
	cout << 1 << endl;
	int n = get(1, 4);
	int k = get(1, n);
	int m = get(1, 4);
	int t = 2;
	cout << n << " " << k << " " << m << " " << t << endl;
	for (int i = 0; i < n; i++)
		cout << get(0, 9);
	cout << endl;
	return 0;
}