#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void read() {


}

void run() {
	double l = 0, r = 2;
	while (abs(l - r) > 1e-9) {
		double mid = (l + r) / 2;
		if (mid * mid <= 2) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	cout << fixed << setprecision(20) << l << endl;
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
