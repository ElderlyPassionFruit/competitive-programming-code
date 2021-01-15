#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int n;

void read() {
	cin >> n;
}

int ans;

void run() {
	ans = 1e9;
	for (int a = 1; ; a++) {
		for (int b = a; ; b++) {
			if (n % (a * b) == 0) { 
				int c = max((n + a * b - 1) / (a * b), 1LL);
				assert(a * b * c >= n);
				//int x =  2 * (a * b + b * c + c * a);
				//if (x == 1992) {
				//	cout << a << " " << b << " " << c << endl;
				//	cout << a * b * c << " " << n << endl;
				//}
				chkmin(ans, 2 * a * b + 2 * a * c + 2 * b * c);
			}
			if (a * b > n) break;
		}
		if (a > n) break;
	}
}

void write() {
	cout << ans << endl;
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