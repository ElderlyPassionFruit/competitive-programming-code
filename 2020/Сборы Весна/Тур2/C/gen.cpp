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

	int n = get(3, 9) * 2;
	vector<int> x(n), y(n);
	iota(all(x), 1);
	iota(all(y), 1);
	for (int i = 1; i < n; i += 2) {
		if (rnd() % 2)
		x[i] = x[i - 1];
		if (rnd() % 2)
		y[i] = y[i - 1]; 
	}
	shuffle(all(x), rnd);
	shuffle(all(y), rnd);
	cout << n << endl;
	for (int i = 0; i < n; i++) {
		cout << x[i] << " " << y[i] << endl; 
	}
	return 0;
}