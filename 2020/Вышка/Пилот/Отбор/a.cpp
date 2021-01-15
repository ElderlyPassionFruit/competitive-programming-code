#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int k;

void read() {
	cin >> k;
}

void run() {
	if (k == 1) {
		cout << "YES\n";
		exit(0);
	}
	for (int n = 3; n <= k; n++) {
		if (4 * n - 4 == k) {
			cout << "YES\n";
			exit(0);
		}
	}
}

void write() {
	cout << "NO\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}