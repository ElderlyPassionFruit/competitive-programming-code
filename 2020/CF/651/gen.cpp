#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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
	int n = 11;
	cout << n << endl;
	string s = "";
	for (int i = 0; i < n; i++) {
		s += get(0, 1) + '0';
	}
	cout << s << endl;
	shuffle(all(s), rnd);
	cout << s << endl;
	return 0;
}