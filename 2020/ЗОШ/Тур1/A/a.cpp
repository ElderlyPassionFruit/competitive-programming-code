#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int l, r;

void read() {
	cin >> l >> r;
}

void run() {
	if (l == r) {
		if (l == 0) {
			cout << "Not a moose" << endl;
		}
		else 
			cout << "Even " << l + r << endl;
	}
	else {
		cout << "Odd " << max(l, r) * 2 << endl;
	}
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