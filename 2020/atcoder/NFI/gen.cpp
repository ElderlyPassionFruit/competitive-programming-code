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

void read() {
	int n = (1 << 18) - 1;
	cout << n << endl;
	for (int i = 0; i < n; i++) {
		cout << get(1, 100000) << " " << get(1, 100000) << endl;
	}
	int q = 100000;
	cout << q << endl;
	for (int i = 0; i < q; i++) {
		cout << get(1, n) << " " << get(1, 100000) << endl;
	}
}

void run() {

}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}