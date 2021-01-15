#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int x;

void read() {
	cin >> x;
}

void run() {
	for (ll a = -4000; a <= 4000; a++) {
		for (ll b = -4000; b <= 4000; b++) {
			ll have = a * a * a * a * a - b * b * b * b * b;
			if (have == x) {
				cout << a << " " << b << endl;
				exit(0);
			}
		}
	}
	assert(false);
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