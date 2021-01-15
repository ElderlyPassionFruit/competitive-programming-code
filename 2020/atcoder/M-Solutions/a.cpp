#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

void read() {
	int a;
	cin >> a;
	int ans;
	if (a <= 599) {
		ans = 8;
	} else if (a <= 799) {
		ans = 7;
	} else if (a <= 999) {
		ans = 6;
	} else if (a <= 1199) {
		ans = 5;
	} else if (a <= 1399) {
		ans = 4;
	} else if (a <= 1599) {
		ans = 3;
	} else if (a <= 1799) {
		ans = 2;
	} else {
		ans = 1;
	}
	cout << ans << endl;
}

void run() {

}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}