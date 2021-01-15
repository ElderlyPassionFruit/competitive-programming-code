#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int k1, b1, k2, b2;

void read() {
	cin >> k1 >> b1 >> k2 >> b2;
}

void run() {
	if (k1 == k2 && b1 == b2) {
		cout << "coincide\n";
	} else if (k1 == k2) {
		cout << "parallel\n";
	} else {
		cout << "intersect\n";
		ld x = (ld)(b2 - b1) / (k1 - k2);
		ld y = k1 * x + b1;
		cout << x << " " << y << endl;
	}
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