#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}
#define int ll
void read() {
	int a, b, c, k;
	cin >> a >> b >> c >> k;
	while (a >= b) {
		b *= 2;
		k--;
	}
	while (b >= c) {
		c *= 2;
		k--;
	}
	if (k >= 0) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
	}
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