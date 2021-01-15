#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int x, y;

void read() {
	cin >> x >> y;
}

int ans;

void run() {
	ans = 0;
	int x1 = y, x2 = y, x3 = y;
	while (x1 != x || x2 != x || x3 != x) {
		//cout << x1 << " " << x2 << " " << x3 << endl;
		if (x1 <= x2 && x1 <= x3) {
			x1 = min(x2 + x3 - 1, x);
		}
		else if (x2 <= x1 && x2 <= x3) {
			x2 = min(x1 + x3 - 1, x);
		}
		else {
			x3 = min(x1 + x2 - 1, x);
		}
		ans++;
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//cout << RAND_MAX << endl;
	read();
	run();
	write();
	return 0;
}