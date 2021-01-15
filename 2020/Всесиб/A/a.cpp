#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m, x, y;

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> x >> y;
	while (true) {
		if (x < 1 || x > n || y < 1 || y > m) {
			cout << "End of program" << endl;
			return 0;
		}
		if (x > 1 && x < n && y > 1 && y < m) {
			cout << "inside ?" << endl;
		}
		else {
			cout << "border ?" << endl;
		}
		char t;
		cin >> t;
		if (t == 'U') x--;
		if (t == 'D') x++;
		if (t == 'L') y--;
		if (t == 'R') y++;
	}
	return 0;
}